#pragma once
#include <drogon/HttpController.h>
#include "ExteriorTempProvider.h"

using namespace drogon;
class Controller: public drogon::HttpController<Controller> {
    ExteriorTempProvider exteriorTempProvider;
public:
    METHOD_LIST_BEGIN
    //use METHOD_ADD to add your custom processing function here;
    //METHOD_ADD(Controller::get,"/{2}/{1}",Get);//path is /Controller/{arg2}/{arg1}
    //METHOD_ADD(Controller::your_method_name,"/{1}/{2}/list",Get);//path is /Controller/{arg1}/{arg2}/list
    //ADD_METHOD_TO(Controller::your_method_name,"/absolute/path/{1}/{2}/list",Get);//path is /absolute/path/{arg1}/{arg2}/list
    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    // void get(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,int p1,std::string p2);
    // void your_method_name(const HttpRequestPtr& req,std::function<void (const HttpResponsePtr &)> &&callback,double p1,int p2) const;
    void setOnPublishInfo(const std::function<void(const std::string&)> &f);
    void checkStatus();
private:
    void getSensorTemp(const std::function<void(bool error, double temp)> &cb);
    void publishInfo();
    void notify(const std::string &subject, const std::string &content);

    bool activeNow = false;

    bool sensorTempError = false;
    double sensorTemp = 0.0;
    bool externalTempError = false;
    double externalTempTemp = 0.0;
    bool peripheralError = false;
    double peripheralTemp = 0.0;
    std::string externalTempImg;

    std::function<void(const std::string&)> onPublishInfo = nullptr;
};
