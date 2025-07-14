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