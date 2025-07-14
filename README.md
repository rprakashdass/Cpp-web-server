# Lightweight, High-Performance C++ Application Framework (POSIX Standard)

A modern, blazing-fast, and extensible C++ framework for building web servers, static sites, REST/RPC APIs, and even desktop/mobile-like runtimes. Inspired by Express, designed for high performance, POSIX compliance, and hackability.

---

## Features
- **Static file serving** (HTML, CSS, JS, assets)
- **Dynamic routing** (REST & RPC-style endpoints)
- **Thread pool-based concurrency** for high throughput
- **CLI-configurable**: port, threads, static directory
- **Extensible**: Compose apps, add middleware, or build full runtimes
- **Cross-platform ambitions**: Web, desktop, iOS, and more
- **Ready for HTTPS** (OpenSSL support coming soon)
- **POSIX standard**: Clean, portable, and robust

---

## Philosophy
This framework is developed as an educational project, created through extensive study and hands-on research into modern C++ practices and framework design. While minimal, modular, and lightning-fast, its primary goal is to serve as a learning tool — showcasing how flexible, high-performance C++ frameworks can be built and extended across diverse application domains.
---

## Folder Structure
```
docs/
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

---

## Build Instructions

### 1. Clone the Repository

```bash
https://github.com/rprakashdass/Cpp-web-server.git
cd Cpp-web-server
```

### 2. Create Build Directory

```bash
mkdir build && cd build
```

### 3. Build with CMake

```bash
cmake ..
make
```

### 4. Run the Server

```bash
./lightcppframework
```

> Note: Ensure `public/` directory is present in the root for static file serving.

---


## Usage Example
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

## API Overview
- `Router::registerRoute(path, handler)` — Register REST endpoints
- `Router::registerAction(action, handler)` — Register RPC-style actions
- `AppDispatcher::HandleRequest(request)` — Unified request handling
- `StaticServer::setStaticDir(path)` — Set static file directory
- CLI: `--port`, `--threads`, `--static`

---

## Extending
- Add custom middleware, handlers, or integrations
- Compose with other C++ libraries
- See `docs/` for extension and architecture guides

---

## Testing
- Unit and integration tests in `tests/` for routing, HTTP parsing, static serving, and thread pool

---

## Contributing
See [CONTRIBUTING.md](CONTRIBUTING.md) and [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md)

---

## License
MIT

---

## Packaging & Reuse
- Headers in `include/` for easy import
- No hardcoded paths; all entrypoints are flexible
- Designed for use as a package in larger C++ projects
- CMake-based build for easy integration

---

## Documentation
See `docs/` for:
- Introduction & getting started
- Architecture & design
- Usage & extension guides
- API reference

---