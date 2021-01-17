#pragma once
#include <drogon/HttpController.h>
#include "ExteriorTempProvider.h"

using namespace drogon;
class Controller: public drogon::HttpController<Controller, false> {
    ExteriorTempProvider exteriorTempProvider;
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(Controller::dashboard,"/",Get, "DigestAuthFilter");
    ADD_METHOD_TO(Controller::dashboard,"/dashboard",Get, "DigestAuthFilter");
    ADD_METHOD_TO(Controller::rules,"/rules",Get, "DigestAuthFilter");
    ADD_METHOD_TO(Controller::config,"/config",Get, "DigestAuthFilter");
    METHOD_LIST_END
    void dashboard(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback) const;
    void rules(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback) const;
    void config(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback);
    void setOnPublishInfo(const std::function<void(const std::string&)> &f);
    void checkStatus();

private:
    void getSensorTemp(const std::function<void(bool error, double temp)> &cb) const;
    void storeInfo() const;
    void publishInfo() const;
    void notify(const std::string &subject, const std::string &content) const;
    double getLimitTemp() const;
    double getHysteresis() const;
    bool activeNow = false;

    bool sensorTempError = false;
    double sensorTemp = 0.0;
    bool externalTempError = false;
    double externalTempTemp = 0.0;
    bool peripheralError = false;
    double peripheralTemp = 0.0;
    std::string externalTempImg;
    trantor::TimerId timerId = 0;
    std::function<void(const std::string&)> onPublishInfo = nullptr;
};
