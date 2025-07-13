#include "../include/Router.h"

void Router::registerAction(const std::string& action, ActionHandler handler) {
    handlers[action] = handler;
}

HTTPResponse Router::dispatchAction(const std::string& path, const std::string& body) const {
    auto it = handlers.find(path);
    if (it != handlers.end()) {
        return HTTPResponse::ok(200, it->second(body));
    }

    return HTTPResponse::error(404, "Action not found");
}