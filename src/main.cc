#include <iostream>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <drogon/HttpController.h>
#include "filters/DigestAuthFilter.h"
#include "Controller.h"
#include "InfoWebSocketController.h"
#include "version.h"

using namespace spdlog;
using namespace drogon;

void initLog(const std::string &appname) {
    auto console_sink = std::make_shared<sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared < sinks::basic_file_sink_mt
            > ("/tmp/homehub.log", false);
    auto l = std::make_shared < logger > (appname, sinks_init_list {
            console_sink, file_sink });
    set_default_logger(l);
    spdlog::flush_every(std::chrono::seconds(3));
    spdlog::set_level(spdlog::level::trace);
}

void printHandlers() {
    spdlog::info(
            "|||||||||||||||||||||||||||HANDLERS||||||||||||||||||||||||||");
    auto handlerInfo = app().getHandlersInfo();
    for (auto &info : handlerInfo) {
        switch (std::get < 1 > (info)) {
        case Get:
            spdlog::info("{0} {1} {2}", std::get < 0 > (info), " (GET) ",
                    std::get < 2 > (info));
            break;
        case Post:
            spdlog::info("{0} {1} {2}", std::get < 0 > (info), " (POST) ",
                    std::get < 2 > (info));
            break;
        case Delete:
            spdlog::info("{0} {1} {2}", std::get < 0 > (info), " (DELETE) ",
                    std::get < 2 > (info));
            break;
        case Put:
            spdlog::info("{0} {1} {2}", std::get < 0 > (info), " (PUT) ",
                    std::get < 2 > (info));
            break;
        case Options:
            spdlog::info("{0} {1} {2}", std::get < 0 > (info), " (OPTIONS) ",
                    std::get < 2 > (info));
            break;
        case Head:
            spdlog::info("{0} {1} {2}", std::get < 0 > (info), " (Head) ",
                    std::get < 2 > (info));
            break;
        default:
            break;
        }
    }
    spdlog::info(
            "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||");
}

int main(int argc, char *argv[]) {
    initLog(argv[0]);
    std::map < std::string, std::string > config_credentials;
    std::string realm("drogonRealm");
    std::string opaque("drogonOpaque");
    std::string config_file = "config.json";
    if (argc > 1) {
        config_file = argv[1];
    }
    app().loadConfigFile(config_file);
    auto &customConfig = app().getCustomConfig();
    if (customConfig.empty()) {
        spdlog::info("empty custom config!");
    } else {
        if (!customConfig["realm"].empty()) {
            realm = customConfig["realm"].asString();
        }
        if (!customConfig["opaque"].empty()) {
            opaque = customConfig["opaque"].asString();
        }
        for (auto &&i : customConfig["credentials"]) {
            config_credentials[i["user"].asString()] = i["password"].asString();
        }
    }

    auto auth_filter = std::make_shared < DigestAuthFilter
            > (config_credentials, realm, opaque);
    app().registerFilter(auth_filter);

    auto infoController = std::make_shared<InfoWebSocketController>();
    app().registerController<InfoWebSocketController>(infoController);

    spdlog::info("Version: {0}, Date: {1}",
            HOMEHUB_VERSION,
            std::string { drogon::utils::getHttpFullDate(trantor::Date::now()) });
    printHandlers();

    auto controller = std::make_shared<Controller>();
    controller->setOnPublishInfo(std::bind(&InfoWebSocketController::publish, infoController, std::placeholders::_1));
    double period = 10.0;
    app().getLoop()->runInLoop(std::bind(&Controller::checkStatus, controller));
    app().run();
}
