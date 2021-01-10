#include "ExteriorTempProvider.h"
#include <drogon/drogon.h>
#include <spdlog/spdlog.h>

using namespace drogon;

ExteriorTempProvider::ExteriorTempProvider() {
    loc = app().getCustomConfig()["openweather-loc"].asString();
    api = app().getCustomConfig()["openweather-api"].asString();
}

void ExteriorTempProvider::getExteriorTemp(
        std::function<void(bool error, double temp, const std::string&)> cb) {
    spdlog::debug("PeripheralDevice::getExteriorTemp");
    cb(false, 0, "img");
//    auto client = HttpClient::newHttpClient("https://api.openweathermap.org");
//    auto req = HttpRequest::newHttpRequest();
//    req->setMethod(drogon::Get);
//    req->setPath("/data/2.5/weather");
//    req->setParameter("units", "metric");
//    req->setParameter("q", loc);
//    req->setParameter("appid", api);
//    client->sendRequest(req,
//            [cb](ReqResult result, const HttpResponsePtr &response) {
//                bool error = true;
//                double t = 0;
//                std::string img;
//                if (result == ReqResult::Ok) {
//                    try {
//                        Json::Value jsonResponse;
//                        Json::Reader jsonReader;
//                        if (jsonReader.parse(
//                                static_cast<std::string>(response->getBody()),
//                                jsonResponse)
//                                && !jsonResponse["main"]["temp"].empty()
//                                && !jsonResponse["weather"].empty()
//                                && !jsonResponse["weather"][0]["icon"].empty()) {
//                            t = jsonResponse["main"]["temp"].asDouble();
//                            img =
//                                    "http://openweathermap.org/img/w/"
//                                            + jsonResponse["weather"][0]["icon"].asString()
//                                            + ".png";
//                            error = false;
//                        }
//                    } catch (...) {
//                    }
//                }
//                spdlog::debug(
//                        "ExteriorTempProvider::getExteriorTemp: error: {0} t: {1} img:{2}",
//                        error, t, img);
//                cb(error, t, img);
//            });
}
