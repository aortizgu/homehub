#pragma once
#include <drogon/WebSocketController.h>
#include <drogon/PubSubService.h>
using namespace drogon;

class InfoWebSocketController: public drogon::WebSocketController<
        InfoWebSocketController, false> {
public:
    WS_PATH_LIST_BEGIN
    WS_PATH_ADD("/info", Get);
    WS_PATH_LIST_END
    virtual void handleNewMessage(const WebSocketConnectionPtr&, std::string&&,
            const WebSocketMessageType&) override;
    virtual void handleConnectionClosed(const WebSocketConnectionPtr&) override;
    virtual void handleNewConnection(const HttpRequestPtr&,
            const WebSocketConnectionPtr&) override;
    void publish(const std::string &msg);
private:
    std::string lastMsg;
    PubSubService<std::string> pubSubService;
};
