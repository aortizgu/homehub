#pragma once
#include <functional>

class ExteriorTempProvider {
    std::string loc,api;
public:
    ExteriorTempProvider();
    void getExteriorTemp(std::function<void(bool error, double temp, const std::string&)>);
};
