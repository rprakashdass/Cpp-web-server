# Extension Guide

This framework is designed to be easily extended for new features, middleware, and integrations.

## Adding Custom Routes
- Use `router.registerRoute("/path", handler)` to add REST endpoints.
- Use `router.registerAction("action", handler)` for RPC-style actions.

## Adding Middleware
- Create a new class or function that processes HTTPRequest/HTTPResponse.
- Integrate it in your main server loop or dispatcher.

## Integrating with Other Libraries
- Use any C++ library for database, authentication, etc.
- Compose your logic in route/action handlers.

## Example: Adding a JSON API Endpoint
```cpp
router.registerRoute("/api/data", [](const std::string& body) {
    // Parse body, process, and return JSON
    return R"({\"result\":42})";
});
```

## Advanced
- Subclass or wrap core classes for custom behavior
- Contribute reusable middleware to the community 