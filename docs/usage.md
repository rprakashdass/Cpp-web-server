# Usage Guide

## Building

```
cmake -B build
cmake --build build
```

## Running the Server

```
./build/server --port 8080 --threads 4 --static public/
```

## Adding Routes

See `src/server.cpp` and the README for examples on registering routes and actions.

## Extending

- Add new files to `src/` and `include/`
- Register new routes or actions in your main application
- See `docs/extension.md` for advanced extension patterns 