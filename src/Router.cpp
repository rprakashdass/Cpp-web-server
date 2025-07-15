#include <NanoHost/Router.h>

void Router::registerAction(const std::string& action, ActionHandler handler) {
    handlers[action] = handler;
}

void Router::registerRoute(const std::string& path, RouteHandler handler) {
    routes[path] = handler;
}

Router::RouteHandler Router::getRoute(const std::string& path) const {
    auto it = routes.find(path);
    if (it != routes.end()) return it->second;
    return nullptr;
}

HTTPResponse Router::dispatchAction(const std::string& path, const std::string& body) const {
    auto it = handlers.find(path);
    if (it != handlers.end()) {
        return HTTPResponse::ok(200, it->second(body));
    }

    return HTTPResponse::error(404, "Action not found");
}

HTTPResponse Router::route(const std::string& path, const std::string& body) const {
    auto it = routes.find(path);
    if (it != routes.end()) {
        return HTTPResponse::ok(200, it->second(body));
    }

    return HTTPResponse::error(404, "Action not found");
}