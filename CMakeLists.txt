cmake_minimum_required(VERSION 3.15)
project(LightweightCppFramework VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main library
add_library(lightcppframework
    src/ActionDispatcher.cpp
    src/AppDispatcher.cpp
    src/HTTPRequest.cpp
    src/HTTPResponse.cpp
    src/Router.cpp
    src/StaticServer.cpp
    src/ThreadPool.cpp
)

# Headers
set_target_properties(lightcppframework PROPERTIES PUBLIC_HEADER "include/ActionDispatcher.h;include/AppDispatcher.h;include/HTTPRequest.h;include/HTTPResponse.h;include/Router.h;include/StaticServer.h;include/ThreadPool.h")
target_include_directories(lightcppframework PUBLIC include)

# Example server binary
add_executable(server src/server.cpp)
target_link_libraries(server PRIVATE lightcppframework)


# Install
install(TARGETS lightcppframework
    EXPORT lightcppframeworkTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include)
install(DIRECTORY include/ DESTINATION include)