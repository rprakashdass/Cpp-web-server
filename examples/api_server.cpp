#include <AppDispatcher.h>
#include <Router.h>
#include <StaticServer.h>
#include <nlohmann/json.hpp>
#include <iostream>

using json = nlohmann::json;

int main() {
    Router router;
    AppDispatcher app(router);
    StaticServer staticServer;
    staticServer.setStaticDir("public");

    // REST endpoint
    router.registerRoute("/api/hello", [](const std::string& body) {
        return R"({\"message\":\"Hello from REST!\"})";
    });

    // RPC-style action
    router.registerAction("sum", [](const std::string& body) {
        try {
            auto j = json::parse(body);
            int a = j.value("a", 0);
            int b = j.value("b", 0);
            return std::string("{\"result\":") + std::to_string(a + b) + "}";
        } catch (...) {
            return std::string(R"({\"error\":\"Invalid JSON\"})");
        }
    });

    // Custom error route
    router.registerRoute("/api/error", [](const std::string&) {
        return R"({\"error\":\"Something went wrong\"})";
    });

    std::cout << "[Example] API server routes registered. See src/server.cpp for full server loop.\n";
    return 0;
} 