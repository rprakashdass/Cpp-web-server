# Advanced Usage

## Middleware
You can add middleware by wrapping or extending the request handling logic. For example, to log all requests:

```cpp
// In your main server loop or dispatcher
HTTPRequest req = HTTPRequest::parse(rawRequest);
std::cout << "[LOG] " << req.method << " " << req.path << std::endl;
HTTPResponse resp = app.HandleRequest(req);
```

## Custom Error Handling
You can register error routes or actions to handle errors gracefully:

```cpp
router.registerRoute("/api/error", [](const std::string&) {
    return R"({\"error\":\"Something went wrong\"})";
});
```

## Integrating with Other Libraries
You can use any C++ library (e.g., for database, authentication, etc.) inside your route or action handlers:

```cpp
router.registerRoute("/api/user", [](const std::string& body) {
    // Use a database library to fetch user info
    // ...
    return R"({\"user\":\"Alice\"})";
});
```

## Asynchronous Operations
Use the thread pool to offload heavy work:

```cpp
pool.enqueueTask([]() {
    // Do background work
});
```

## See Also
- [API Reference](./api.md)
- [Extension Guide](./extension.md) 