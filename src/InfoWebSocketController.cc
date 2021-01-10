#include "InfoWebSocketController.h"
#include <spdlog/spdlog.h>

void InfoWebSocketController::handleNewMessage(
        const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
        const WebSocketMessageType &type) {
}

void InfoWebSocketController::handleConnectionClosed(
        const WebSocketConnectionPtr &conn) {
    spdlog::info(
            "InfoWebSocketController::handleNewConnection: websocket closed");
    auto &id = conn->getContextRef<drogon::SubscriberID>();
    pubSubService.unsubscribe("InfoWebSocketController", id);
}

void InfoWebSocketController::handleNewConnection(const HttpRequestPtr &req,
        const WebSocketConnectionPtr &conn) {
    spdlog::info(
            "InfoWebSocketController::handleNewConnection: new websocket connection");
    if (!lastMsg.empty()) {
        conn->send(lastMsg);
    }
    drogon::SubscriberID id = pubSubService.subscribe("InfoWebSocketController",
            [conn](const std::string &topic, const std::string &message) {
                conn->send(message);
            });
    conn->setContext(std::make_shared < drogon::SubscriberID > (std::move(id)));
}

void InfoWebSocketController::publish(const std::string &msg) {
    lastMsg = msg;
    spdlog::debug("InfoWebSocketController::publish: {}", msg);
    pubSubService.publish("InfoWebSocketController", msg);
}
