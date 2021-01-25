#include "Controller.h"

#include <unistd.h>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <locale>
#include <iostream>
#include <iomanip>
#include <ctime>

#include "drogon/HttpAppFramework.h"
#include "spdlog/spdlog.h"
#include "mail/MAILClient.h"
#include "mail/SMTPClient.h"
#include "model/Measurement.h"
#include "model/Config.h"
#include "PeripheralDevice.h"

using namespace drogon_model::sqlite3;

void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

void Controller::dashboard(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback) const {
    spdlog::info("Controller::dashboard");
    auto resp = HttpResponse::newHttpViewResponse("dashboard.csp");
    try {
        Mapper<Measurement> mp(app().getDbClient());
        auto measurements = mp.findAll();

        Json::Value measurementsJson;
        for (int i = 0; i < measurements.size(); ++i) {
            measurementsJson[i] = measurements[i].toJson();
        }
        HttpViewData data;
        data.insert("measurementsJson", measurementsJson.toStyledString());
        resp = HttpResponse::newHttpViewResponse("dashboard.csp", data);
    } catch (const DrogonDbException &e) {
        resp->setStatusCode(HttpStatusCode::k500InternalServerError);
        spdlog::error("Controller::dashboard: exception {0}", e.base().what());
    }
    callback(resp);
}

void Controller::rules(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback) const {
    spdlog::info("Controller::rules");
    auto resp = HttpResponse::newHttpViewResponse("rules.csp");
    try {
        Mapper<Config> mp(app().getDbClient());
        Config config = mp.findByPrimaryKey(1);
        HttpViewData data;
        data.insert("config", config);
        if (!req->getCookie("message").empty()) {
            data.insert("message", req->getCookie("message"));
        }
        resp = HttpResponse::newHttpViewResponse("rules.csp", data);
    } catch (...) {
        resp->setStatusCode(HttpStatusCode::k400BadRequest);
    }
    resp->addCookie("message", "");
    callback(resp);
}

void Controller::config(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback) {
    auto resp = HttpResponse::newRedirectionResponse("/rules");
    try {
        Config config;
        std::string::size_type sz;
        config.setId(1);
        config.setLimittemp(std::stod(req->getParameter("limit"), &sz));
        config.setHysteresis(std::stod(req->getParameter("hyst"), &sz));
        Mapper<Config> mp(app().getDbClient());
        mp.update(config);
        resp->addCookie("message", "Configuración modificada");
        spdlog::info("Controller::config: config updated");
        app().getLoop()->queueInLoop(std::bind(&Controller::checkStatus, this));
    } catch (...) {
        resp->setStatusCode(HttpStatusCode::k400BadRequest);
    }
    callback(resp);
}

void Controller::setOnPublishInfo(const std::function<void(const std::string&)> &f) {
    onPublishInfo = f;
}

void Controller::checkStatus() {
    if (first) {
        notify("Inicio de aplicación", "(·_·)");
        first = false;
    }
    spdlog::info("Controller::checkStatus: stop timer {}", timerId);
    app().getLoop()->invalidateTimer(timerId);
    /*
     * 1-getExternalTemp
     * 2-getSensorTemp
     * 3-setPeripheralState
     * 4-getPeripheralTemp
     * 5-storeInfo
     * 6-publishInfo
     */
    exteriorTempProvider.getExteriorTemp([this](bool error, double temp, const std::string &img) {
        spdlog::debug("Controller::getExteriorTemp: error {0}, temp {1}, img {2}", error, temp, img);
        if (externalTempError != error) {
            spdlog::error("Controller::checkStatus::getExteriorTemp: error {} -> {}", externalTempError, error);
            if (error) {
                notify("Servicio de temperatura exterior",
                        "Se ha producido un error tratando de obtener la información acerca de la temperatura exterior");
            } else {
                notify("Servicio de temperatura exterior",
                        "Se ha reestablecido la comunicación con el servicio de temperatura exterior");
            }
            externalTempError = error;
        }
        if (!error) {
            externalTempTemp = temp;
            externalTempImg = img;
        }

        getSensorTemp([this](bool error, double temp) {
            spdlog::debug("Controller::getSensorTemp: error {0}, temp {1}", error, temp);
            if (sensorTempError != error) {
                spdlog::error("Controller::checkStatus::getSensorTemp: error {} -> {}", sensorTempError, error);
                if (error) {
                    notify("Sensor de temperatura",
                            "Se ha producido un error tratando de obtener la información acerca del sensor de temperatura");
                } else {
                    notify("Sensor de temperatura",
                            "Se ha reestablecido la comunicación con el sensor de temperatura");
                }
                sensorTempError  = error;
            }

            if (!error) {
                sensorTemp = temp;

                bool mustActivate = false;
                double limitTemp = getLimitTemp();
                double hysteresis = getHysteresis();
                if (activeNow) {
                    mustActivate = sensorTemp < limitTemp + hysteresis;
                } else {
                    mustActivate = sensorTemp < limitTemp - hysteresis;
                }

                spdlog::debug("Controller::getSensorTemp: sensorTemp {0}, limitTemp {1}, hysteresis {2}, mustActivate {3}, activeNow {4}", sensorTemp, limitTemp, hysteresis, mustActivate, activeNow);

                if (activeNow != mustActivate) {
                    spdlog::info("Controller::checkStatus: active {} -> {}", activeNow, mustActivate);
                    activeNow = mustActivate;
                    std::ostringstream ss;
                    ss << std::setprecision(2);
                    if (activeNow) {
                        ss << "Se ha encendido la calefación. Temperatura actual " << sensorTemp << " ºC, configurado a " << limitTemp << " ºC.";
                        notify("Calefacción Encendida", ss.str());
                    } else {
                        ss << "Se ha apagado la calefación. Temperatura actual " << sensorTemp << " ºC, configurado a " << limitTemp << " ºC.";
                        notify("Calefacción Apagada", ss.str());
                    }
                }
            } else {
                activeNow = false;
            }

            PeripheralDevice::setState(activeNow, [this](bool error){
                spdlog::debug("Controller::setState: error {0}", error);
                if (peripheralError != error) {
                    spdlog::error("Controller::checkStatus::setState: error {} -> {}", peripheralError, error);
                    if (error) {
                        notify("Dispositivo Periférico",
                                "Se ha producido un error tratando de obtener la información acerca del Dispositivo Periférico");
                    } else {
                        notify("Dispositivo Periférico",
                                "Se ha reestablecido la comunicación con el Dispositivo Periférico");
                    }
                    peripheralError  = error;
                }

                PeripheralDevice::getTemp([this](bool error, double temp){
                    spdlog::debug("Controller::getTemp: error {0}, temp {1}", error, temp);
                    if (peripheralError != error) {
                        spdlog::error("Controller::checkStatus::getTemp: error {} -> {}", peripheralError, error);
                        if (error) {
                            notify("Dispositivo Periférico",
                                    "Se ha producido un error tratando de obtener la información acerca del Dispositivo Periférico");
                        } else {
                            notify("Dispositivo Periférico",
                                    "Se ha reestablecido la comunicación con el Dispositivo Periférico");
                        }
                        peripheralError  = error;
                    }

                    if (!error) {
                        peripheralTemp = temp;
                    }

                    storeInfo();
                    publishInfo();

                    timerId = app().getLoop()->runAfter(app().getCustomConfig()["controller"]["period"].asDouble(), std::bind(&Controller::checkStatus, this));
                    spdlog::debug("Controller::checkStatus: period {}, setting timerId {}", app().getCustomConfig()["controller"]["period"].asDouble(), timerId);
                });
            });
        });
    });
}

void Controller::getSensorTemp(const std::function<void(bool error, double temp)> &cb) const {
    const std::string enumerationSlavesFile(
            "/sys/bus/w1/devices/w1_bus_master1/w1_master_slaves");
    if (access(enumerationSlavesFile.c_str(), R_OK)) {
        spdlog::error("Controller::getSensorTemp: cannot access enumerationSlavesFile");
        cb(true, 0);
        return;
    }
    std::string sensor;
    std::ifstream sensorEnumerationFileStream(enumerationSlavesFile);
    if (!std::getline(sensorEnumerationFileStream, sensor)) {
        spdlog::error("Controller::getSensorTemp: cannot read from enumerationSlavesFile");
        cb(true, 0);
        return;
    }
    sensorEnumerationFileStream.close();

    std::string slaveTempFile = "/sys/bus/w1/devices/";
    trim(sensor);
    slaveTempFile += sensor;
    slaveTempFile += "/temperature";
    if (access(slaveTempFile.c_str(), R_OK)) {
        spdlog::error("Controller::getSensorTemp: cannot access slave temp file");
        cb(true, 0);
        return;
    }

    std::ifstream slaveTempFileStream(slaveTempFile);
    std::string tempString;
    if (!std::getline(slaveTempFileStream, tempString)) {
        spdlog::error("Controller::getSensorTemp: cannot read from slave temp file");
        cb(true, 0);
        return;
    }
    slaveTempFileStream.close();
    try {
        double temp = std::stod(tempString) / 1000.0;
        cb(false, temp);
    } catch (...) {
        spdlog::error("Controller::getSensorTemp: cannot convert temperature string to double %s", tempString.c_str());
        cb(true, 0);
    }
}

void Controller::storeInfo() const {
    Measurement m;
    m.setActive(activeNow);
    m.setLimittempconfigured(getLimitTemp());
    m.setDate(time(nullptr));
    m.setTempcald(peripheralTemp);
    m.setTempexterior(externalTempTemp);
    m.setTempinterior(sensorTemp);

    try {
        Mapper<Measurement> mp(app().getDbClient());
        mp.insert(m);

        auto result =
                app().getDbClient()->execSqlSync(
                        "DELETE FROM measurement WHERE ROWID IN (SELECT ROWID FROM measurement ORDER BY ROWID DESC LIMIT -1 OFFSET $1)",
                        24 * 60 * 60 / app().getCustomConfig()["controller"]["period"].asInt());
    } catch (const DrogonDbException &e) {
        spdlog::error("Controller::storeInfo: db error {0}", e.base().what());
    }
}

void Controller::publishInfo() const {
    if (onPublishInfo) {
        Json::Value info;
        info["int"]["temp"] = sensorTemp;
        info["int"]["error"] = sensorTempError;
        info["cald"]["temp"] = peripheralTemp;
        info["cald"]["error"] = peripheralError;
        info["ext"]["temp"] = externalTempTemp;
        info["ext"]["img"] = externalTempImg;
        info["ext"]["error"] = externalTempError;
        info["active"] = activeNow;
        info["manual"] = true;
        info["status"] = !sensorTempError && !peripheralError && !externalTempError;
        info["limitTemp"] = getLimitTemp();
        info["hysteresis"] = getHysteresis();
        onPublishInfo(info.toStyledString());
    }
}

void Controller::notify(const std::string &subject, const std::string &content) const {
    spdlog::debug("Controller::notify: subject {0}, content {1}", subject, content);
    auto &config = app().getCustomConfig()["controller"]["mail"];
    if (!config["subscriptors"].empty()) {
        CSMTPClient SMTPClient([](const std::string &t) { spdlog::debug(t); } );
        SMTPClient.InitSession(config["server"].asString(), config["user"].asString(), config["password"].asString(),
                CMailClient::SettingsFlag::ALL_FLAGS, CMailClient::SslTlsFlag::ENABLE_SSL);
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream subjectss;
        subjectss << subject;
        subjectss << std::put_time(&tm, " %H:%M:%S");
        for (auto &&subscriptor : config["subscriptors"]) {
            if (!SMTPClient.SendString(config["from"].asString(), subscriptor.asString(), "", subjectss.str(), content)) {
                spdlog::error("Controller::notify: cannot send mail to {0}", subscriptor.asString());
            }
        }
    }
}

double Controller::getLimitTemp() const {
    double ret = app().getCustomConfig()["controller"]["limit-temp"].asDouble();
    try {
        Mapper<Config> mp(app().getDbClient());
        ret = mp.findByPrimaryKey(1).getValueOfLimittemp();
    } catch (...) {
    }
    return ret;
}

double Controller::getHysteresis() const {
    double ret = app().getCustomConfig()["controller"]["hysteresis"].asDouble();
    try {
        Mapper<Config> mp(app().getDbClient());
        ret = mp.findByPrimaryKey(1).getValueOfHysteresis();
    } catch (...) {
    }
    return ret;
}
