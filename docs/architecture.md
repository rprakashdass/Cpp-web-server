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