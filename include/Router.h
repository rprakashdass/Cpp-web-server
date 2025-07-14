#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <functional>
#include <unordered_map>
#include "../include/HTTPResponse.h"

class Router {
public:
    using ActionHandler = std::function<std::string(const std::string& body)>;
    using RouteHandler = std::function<std::string(const std::string& body)>;

    HTTPResponse dispatchAction(const std::string& path, const std::string& body) const;
    HTTPResponse route(const std::string& path, const std::string& body) const;

    Router::RouteHandler getRoute(const std::string& path) const;

    void registerRoute(const std::string& path, RouteHandler handler);
    void registerAction(const std::string& action, ActionHandler handler);
private:
    std::unordered_map<std::string, ActionHandler> handlers;
    std::unordered_map<std::string, ActionHandler> routes;
};

#endif