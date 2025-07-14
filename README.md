# Lightweight, High-Performance C++ Application Framework (POSIX Standard)

A modern, blazing-fast, and extensible C++ framework for building web servers, static sites, REST/RPC APIs, and even desktop/mobile-like runtimes. Inspired by Express, designed for high performance, POSIX compliance, and hackability.

---

## ✨ Features
- **Static file serving** (HTML, CSS, JS, assets)
- **Dynamic routing** (REST & RPC-style endpoints)
- **Thread pool-based concurrency** for high throughput
- **CLI-configurable**: port, threads, static directory
- **Extensible**: Compose apps, add middleware, or build full runtimes
- **Cross-platform ambitions**: Web, desktop, iOS, and more
- **Ready for HTTPS** (OpenSSL support coming soon)
- **POSIX standard**: Clean, portable, and robust

---

## 🚀 Philosophy
This framework is for developers who want the power and performance of C++ with the flexibility of modern frameworks. Minimal, modular, and lightning-fast, it is designed to be hackable and extendable for any application domain.

---

## 📁 Project Structure
```
include/        # Public headers (for package users)
src/            # Core implementation
public/         # Static assets (default static dir)
docs/           # Documentation, guides, architecture
examples/       # Example apps (static, API, etc.)
tests/          # Unit/integration tests
```

---

## ⚡ Quick Start
```sh
# Clone and build
cmake -B build
cmake --build build

# Run the server
./build/server --port 8080 --threads 4 --static public/
```

---

## 📝 Usage Example
```cpp
#include <AppDispatcher.h>
#include <Router.h>

int main() {
    Router router;
    AppDispatcher app(router);
    router.registerRoute("/hello", [](const std::string&) {
        return "Hello, world!";
    });
    // ... add more routes or actions
    // app.listen(8080); // (see server.cpp for entrypoint)
}
```

---

## 🛠 API Overview
- `Router::registerRoute(path, handler)` — Register REST endpoints
- `Router::registerAction(action, handler)` — Register RPC-style actions
- `AppDispatcher::HandleRequest(request)` — Unified request handling
- `StaticServer::setStaticDir(path)` — Set static file directory
- CLI: `--port`, `--threads`, `--static`

---

## 🧩 Extending
- Add custom middleware, handlers, or integrations
- Compose with other C++ libraries
- See `docs/` for extension and architecture guides

---

## 🧪 Testing
- Unit and integration tests in `tests/` for routing, HTTP parsing, static serving, and thread pool

---

## 🤝 Contributing
See [CONTRIBUTING.md](CONTRIBUTING.md) and [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md)

---

## 📄 License
MIT

---

## 📦 Packaging & Reuse
- Headers in `include/` for easy import
- No hardcoded paths; all entrypoints are flexible
- Designed for use as a package in larger C++ projects
- CMake-based build for easy integration

---

## 📚 Documentation
See `docs/` for:
- Introduction & getting started
- Architecture & design
- Usage & extension guides
- API reference

---

## Example Folder Structure
```
docs/
examples/
include/
public/
src/
tests/
CMakeLists.txt
README.md
LICENSE
.gitignore
CONTRIBUTING.md
CODE_OF_CONDUCT.md
```

