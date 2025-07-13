#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <functional>
#include <unordered_map>
#include "../include/HTTPResponse.h"

class Router {
public:
    using ActionHandler = std::function<std::string(const std::string& body)>;

    void registerAction(const std::string& action, ActionHandler handler);
    HTTPResponse dispatchAction(const std::string& path, const std::string& body) const;

private:
    std::unordered_map<std::string, ActionHandler> handlers;
};

#endif