# Architecture Overview

## Core Components
- **Router**: Handles dynamic routing for REST and RPC endpoints.
- **StaticServer**: Serves static files from a configurable directory.
- **ThreadPool**: Manages worker threads for high concurrency.
- **AppDispatcher**: Central dispatcher for routing and static serving.

## Design Principles
- Modular, single-responsibility classes
- POSIX-compliant system calls
- No hardcoded paths; everything is configurable
- Designed for extension and integration

## Extending
- Add new route handlers, actions, or middleware
- Compose with other C++ libraries
- See `docs/extension.md` for more details. 


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
router.registerRoute("/api/data", [](const std::string& /*body*/) {
    // Parse body, process, and return JSON
    return R"({\"result\":42})";
});
```

## Advanced
- Subclass or wrap core classes for custom behavior
- Contribute reusable middleware to the community 


# API Reference

## Router
- `registerRoute(path, handler)` — Register a REST endpoint
- `registerAction(action, handler)` — Register an RPC-style action
- `dispatchAction(path, body)` — Dispatch an action
- `route(path, body)` — Dispatch a route

## AppDispatcher
- `AppDispatcher(router)` — Construct with a Router
- `HandleRequest(request)` — Handle an HTTPRequest and return HTTPResponse

## StaticServer
- `setStaticDir(path)` — Set the static file directory
- `serve(path)` — Serve a static file

## ThreadPool
- `ThreadPool(n)` — Create a thread pool with n threads
- `enqueueTask(fn)` — Add a task to the pool
- `waitAll()` — Wait for all tasks to finish

## HTTPRequest/HTTPResponse
- `HTTPRequest::parse(raw)` — Parse a raw HTTP request
- `HTTPResponse::ok(code, body)` — Create a 200 OK response
- `HTTPResponse::error(code, message)` — Create an error response
- `HTTPResponse::to_string()` — Serialize response 