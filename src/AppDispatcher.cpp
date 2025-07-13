#include "../include/AppDispatcher.h"

AppDispatcher::AppDispatcher(Router& router, const std::string& staticDir)
    : router(router), actionDispatcher(router), staticServer(staticDir) {};

HTTPResponse AppDispatcher::HandleRequest(const HTTPRequest& request) {
    const std::string& path = request.path;
    const std::string& method = request.method;

    // try Json style routing
    auto contentTypeIt = request.headers.find("Content-Type");
    if(method == "POST" && contentTypeIt != request.headers.end() && contentTypeIt->second == "application/json") {
        std::cout << "try Json style routing : " << path << "\n";
        return actionDispatcher.dispatch(request);
    }

    // serve static file
    return staticServer.serve(path);
}