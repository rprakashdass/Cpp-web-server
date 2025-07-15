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

## Installation & Setup

### Recommended: Install via [vcpkg](https://github.com/microsoft/vcpkg)

You can easily install **NanoHost** using [vcpkg](https://github.com/microsoft/vcpkg), the C++ package manager:

```bash
# Step 1: Navigate to your vcpkg directory
cd /path/to/vcpkg

# Step 2: Add the NanoHost port (assuming your port is local or published)
./vcpkg install nanohost
```

Then, in your CMake project:

```cmake
find_package(NanoHost CONFIG REQUIRED)
target_link_libraries(your_project PRIVATE NanoHost)
```

Now you can include headers like:

```cpp
#include <NanoHost/AppDispatcher.h>
#include <NanoHost/Router.h>
```

---

### Build from Source (GitHub Clone)

If you prefer building it directly:

```bash
git clone https://github.com/rprakashdass/nanohost.git
cd nanohost
mkdir build && cd build
cmake ..
make
```

You’ll get a sample server binary (`NanoHostApp`) and the NanoHost static library.

---

### Add to Your Project (Manual Integration)

If you want to embed NanoHost in your own project manually:

1. Copy the `include/NanoHost/` and `src/` folders into your project.
2. Add NanoHost source files to your `CMakeLists.txt`:

   ```cmake
   add_subdirectory(nanohost)
   target_link_libraries(your_project PRIVATE NanoHost)
   ```

---

## Header-Only Usage (for Rapid Prototyping)

While NanoHost uses `.cpp` files and is not strictly header-only, you can include only specific headers if you’re building small modules or custom builds:

```cpp
#include <NanoHost/Router.h>
#include <NanoHost/HTTPResponse.h>
```

Just make sure to link the implementation files or library.

---

## Folder Structure Overview

```bash
docs/           # Documentation and guides
include/        # Public headers (NanoHost/)
public/         # Static assets directory
src/            # Source files
tests/          # Unit and integration tests
CMakeLists.txt  # Build system
README.md       # Project overview
```

---

## Example Usage

```cpp
#include <NanoHost/AppDispatcher.h>
#include <NanoHost/Router.h>

int main() {
    Router router;
    AppDispatcher app(router);

    router.registerRoute("/hello", [](const std::string&) {
        return "Hello from NanoHost!";
    });

    // app.listen(11111);
}
```

---

## Post-Installation Notes

* Run the `NanoHostApp` executable (or your own linked app) from the root folder.
* Make sure the `public/` folder exists for static file hosting.
* Use CLI flags like `--port`, `--threads`, and `--static` for customization.

---


## Usage Example
```cpp
#include <NanoHost/AppDispatcher.h>
#include <NanoHost/Router.h>

int main() {
    Router router;
    AppDispatcher app(router);
    router.registerRoute("/hello", [](const std::string&) {
        return "Hello, world!";
    });
    // ... add more routes or actions
    // app.listen(8080); // (see main.cpp for entrypoint)
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
- Headers in `include/NanoHost/` for easy import
- No hardcoded paths; all entrypoints are flexible
- Designed for use as a package in larger C++ projects
- CMake-based build for easy integration

---