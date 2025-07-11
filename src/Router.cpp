#include "../include/Router.h"

void Router::addRoute(const std::string& path, HandlerFunc handler) {
    routes[path] = handler;
}

std::string Router::route(const std::string& path, const std::string body) {
    if(routes.find(path) == routes.end()) {
        return "404 Not Found";
    } else {
        std::cout << "Routing to " << path << std::endl;
        return routes[path](body);
    }
}