cmake_minimum_required(VERSION 3.15)

project(NanoHost VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main library target
add_library(NanoHost
    src/ActionDispatcher.cpp
    src/AppDispatcher.cpp
    src/HTTPRequest.cpp
    src/HTTPResponse.cpp
    src/Router.cpp
    src/StaticServer.cpp
    src/ThreadPool.cpp
)

# Public headers
target_include_directories(NanoHost
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(NanoHost PROPERTIES
    PUBLIC_HEADER
        "include/NanoHost/NanoHost.h;
        include/NanoHost/ActionDispatcher.h;
        include/NanoHost/AppDispatcher.h;
        include/NanoHost/HTTPRequest.h;
        include/NanoHost/HTTPResponse.h;
        include/NanoHost/Router.h;
        include/NanoHost/StaticServer.h;
        include/NanoHost/ThreadPool.h"
)

# Example executable (can be renamed later or moved to /examples)
add_executable(NanoHostApp src/main.cpp)
target_link_libraries(NanoHostApp PRIVATE NanoHost)

# Install library and headers
install(TARGETS NanoHost
    EXPORT NanoHostTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

# Install headers (optional, already handled above)
install(DIRECTORY include/NanoHost DESTINATION include)

# Export target for reuse
install(EXPORT NanoHostTargets
    FILE NanoHostTargets.cmake
    NAMESPACE NanoHost::
    DESTINATION lib/cmake/NanoHost
)