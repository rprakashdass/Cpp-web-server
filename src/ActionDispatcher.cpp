#include "../include/ActionDispatcher.h"

ActionDispatcher::ActionDispatcher(Router& r) : router(r) {}

HTTPResponse ActionDispatcher::dispatch(const HTTPRequest& request) {
    try {
        json bodyJson = json::parse(request.body);
        if (!bodyJson.contains("action")) {
            return HTTPResponse::error(400, "Missing 'action' in request body");
        }

        std::string action = bodyJson["action"];
        return router.dispatchAction(action, request.body);

    } catch (const json::parse_error& e) {
        return HTTPResponse::error(400, "Invalid JSON in request body");
    } catch (const std::exception& e) {
        return HTTPResponse(500, "Internal Server Error");
    }
}