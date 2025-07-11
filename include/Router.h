#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <iostream>
#include <functional>
#include <unordered_map>

class Router {
public:
    using HandlerFunc = std::function<std::string(const std::string&)>;

    void addRoute(const std::string& path, HandlerFunc handler);
    std::string route(const std::string& path, const std::string);
private:
    std::unordered_map<std::string, HandlerFunc> routes;
};

#endif