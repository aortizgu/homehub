#include "Controller.h"
#include <spdlog/spdlog.h>
#include "ExteriorTempProvider.h"
#include "PeripheralDevice.h"
#include "mail/SMTPClient.h"
#include <algorithm>
#include <cctype>
#include <locale>
#include <fstream>
#include <unistd.h>

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

void Controller::setOnPublishInfo(const std::function<void(const std::string&)> &f) {
    onPublishInfo = f;
}

void Controller::checkStatus() {
    spdlog::debug("Controller::checkStatus");
    /*
     * 1-getExternalTemp
     * 2-getSensorTemp
     * 3-setPeripheralState
     * 4-getPeripheralTemp
     * 4-publishInfo
     */
    exteriorTempProvider.getExteriorTemp([this](bool error, double temp, const std::string &img) {
        spdlog::debug("Controller::getExteriorTemp: error {0}, temp {1}, img {2}", error, temp, img);
        if (externalTempError != error) {
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
                auto &config = app().getCustomConfig()["controller"];
                bool manual = config["manual"].asBool();
                double limitTemp = config["limit-temp"].asDouble();
                double hysteresis = config["hysteresis"].asDouble();

                if (activeNow) {
                    mustActivate = sensorTemp < limitTemp + hysteresis;
                } else {
                    mustActivate = sensorTemp < limitTemp - hysteresis;
                }
                if (activeNow != mustActivate) {
                    activeNow = mustActivate;
                    if (activeNow) {
                        notify("Calefacción Encendida", "");
                    } else {
                        notify("Calefacción Apagada", "");
                    }
                }
            } else {
                activeNow = false;
            }

            PeripheralDevice::setState(activeNow, [this](bool error){
                spdlog::debug("Controller::setState: error {0}", error);
                if (peripheralError != error) {
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

                    publishInfo();

                    auto &config = app().getCustomConfig()["controller"];
                    double period = 10.0;
                    if(!config["period"].empty()) {
                        period = config["period"].asDouble();
                    }
                    spdlog::debug("Controller::checkStatus: period {}", period);
                    app().getLoop()->runAfter(period, std::bind(&Controller::checkStatus, this));
                });
            });
        });
    });
}

void Controller::getSensorTemp(const std::function<void(bool error, double temp)> &cb) {
    spdlog::debug("Controller::getSensorTemp");
    std::string slaveTempFile("/tmp/test_temp");
    if (access(slaveTempFile.c_str(), R_OK)) {
        spdlog::error("Controller::getSensorTemp: cannot access temperature file");
        cb(true, 0);
        return;
    }
    std::string tempString;
    std::ifstream slaveTempFileStream(slaveTempFile);
    if (!std::getline(slaveTempFileStream, tempString)) {
        spdlog::error("Controller::getSensorTemp: cannot read from temperature file");
        cb(true, 0);
        return;
    }
    try {
        double temp = std::stod(tempString) / 1000.0;
        cb(false, temp);
    } catch (...) {
        spdlog::error("Controller::getSensorTemp: cannot convert temperature string to double %s", tempString.c_str());
        cb(true, 0);
    }

//    const std::string enumerationSlavesFile(
//            "/sys/bus/w1/devices/w1_bus_master1/w1_master_slaves");
//    std::string sensor;
//    if (!access(enumerationSlavesFile.c_str(), R_OK)) {
//        std::ifstream enumerationSlavesFileStream(enumerationSlavesFile);
//        if (std::getline(enumerationSlavesFileStream, sensor)) {
//            std::string slaveTempFile = "/sys/bus/w1/devices/";
//            trim(sensor);
//            slaveTempFile += sensor;
//            slaveTempFile += "/temperature";
//            std::string tempString;
//            if (!access(slaveTempFile.c_str(), R_OK)) {
//                std::ifstream slaveTempFileStream(slaveTempFile);
//                if (std::getline(slaveTempFileStream, tempString)) {
//                    try {
//                        ret = std::stod(tempString) / 1000.0;
//                    } catch (...) {
//                        spdlog::error(
//                                "Controller::getSensorTemp: cannot convert temperature string to double %s",
//                                tempString.c_str());
//                    }
//                } else {
//                    spdlog::error(
//                            "Controller::getSensorTemp: cannot read from temperature file");
//                }
//            } else {
//                spdlog::error(
//                        "Controller::getSensorTemp: cannot access temperature file");
//            }
//        } else {
//            spdlog::error(
//                    "Controller::getSensorTemp: cannot read from slaves enumeration file");
//        }
//    } else {
//        spdlog::error(
//                "Controller::getSensorTemp: cannot access to slaves enumeration file");
//    }
}

void Controller::publishInfo() {
    if (onPublishInfo) {
        Json::Value info;
        info["ext"]["temp"] = externalTempTemp;
        info["ext"]["img"] = externalTempImg;
        info["active"] = activeNow;
        onPublishInfo(info.toStyledString());
    }
}

void Controller::notify(const std::string &subject, const std::string &content) {
    spdlog::debug("Controller::notify: subject {0}, content {1}", subject, content);
    auto &config = app().getCustomConfig()["controller"]["mail"];
    if (!config["subcriptors"].empty()) {
        CSMTPClient SMTPClient([](const std::string &t) {
            spdlog::debug(t);
        });
        SMTPClient.InitSession(config["server"].asString(), config["user"].asString(), config["password"].asString(),
                CMailClient::SettingsFlag::ALL_FLAGS,
                CMailClient::SslTlsFlag::ENABLE_SSL);
        for(auto && subscriptor : config["subcriptors"]) {
            if (!SMTPClient.SendString(config["from"].asString(), subscriptor.asString(), "", subject, content)) {
                spdlog::error("Controller::notify: cannot send mail to {0}", subscriptor.asString());
            }
        }
    }
}
