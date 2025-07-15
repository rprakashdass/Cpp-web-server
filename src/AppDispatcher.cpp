#include <NanoHost/AppDispatcher.h>

AppDispatcher::AppDispatcher(Router& router)
    : router(router), actionDispatcher(router) {};

HTTPResponse AppDispatcher::HandleRequest(const HTTPRequest& request) {
    const std::string& path = request.path;
    const std::string& method = request.method;

    // try Json style routing
    auto contentTypeIt = request.headers.find("Content-Type");
    if(method == "POST" && contentTypeIt != request.headers.end() && contentTypeIt->second == "application/json") {
        return actionDispatcher.dispatch(request);
    }

    // Check if registered route
    auto routeHandler = router.getRoute(path);
    if (routeHandler) {
        return router.route(request.path, request.body);
    }

    // serve static file
    return StaticServer::serve(path);
}