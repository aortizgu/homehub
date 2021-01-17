#include "PeripheralDevice.h"
#include <spdlog/spdlog.h>
#include <drogon/drogon.h>

using namespace drogon;

void PeripheralDevice::getTemp(std::function<void(bool error, double temp)> cb) {
    spdlog::debug("PeripheralDevice::getTemp");
    cb(false, 13.0);
    return;
    auto client = HttpClient::newHttpClient("http://caldera.local");
    auto req = HttpRequest::newHttpRequest();
    req->setMethod(drogon::Get);
    req->setPath("/temp");
    client->sendRequest(req, [cb](ReqResult result, const HttpResponsePtr &response) {
        double t = 0;
        bool error = true;
        if (result == ReqResult::Ok) {
            try {
                t = std::stod(static_cast<std::string>(response->getBody()));
                error = false;
            } catch (...) {
            }
        }
        cb(error, t);
    });
}

void PeripheralDevice::getUpTime(std::function<void(bool error, const std::string &uptime)> cb) {
    spdlog::debug("PeripheralDevice::getUpTime");
    auto client = HttpClient::newHttpClient("http://caldera.local");
    auto req = HttpRequest::newHttpRequest();
    req->setMethod(drogon::Get);
    req->setPath("/uptime");
    client->sendRequest(req, [cb](ReqResult result, const HttpResponsePtr &response) {
        std::string uptime;
        bool error = true;
        if (result == ReqResult::Ok) {
            uptime = static_cast<std::string>(response->getBody());
        }
        cb(error, uptime);
    });
}

void PeripheralDevice::setState(bool on, std::function<void(bool error)> cb) {
    spdlog::debug("PeripheralDevice::setState: on:{}", on);
    cb(false);
//    auto client = HttpClient::newHttpClient("http://caldera.local");
//    auto req = HttpRequest::newHttpRequest();
//    req->setMethod(drogon::Get);
//    req->setPath("/relay");
//    req->setParameter("state", on ? "on" : "off");
//    client->sendRequest(req,
//            [cb](ReqResult result, const HttpResponsePtr &response) {
//                cb(result != ReqResult::Ok);
//            });
}
