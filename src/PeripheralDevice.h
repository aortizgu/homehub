#pragma once
#include <functional>

class PeripheralDevice {
public:
    static void getTemp(std::function<void(bool error, double temp)> cb);
    static void getUpTime(std::function<void(bool error, const std::string &uptime)> cb);
    static void setState(bool on, std::function<void(bool error)> cb);
};
