/**********************************************************
 * File        : server.cpp
 * Description : Entry point for lightweight C++ HTTP server
 * Author      : Prakash Dass R
 * Created On  : 2025-07-12
 * License     : MIT
 **********************************************************/

#include <iostream>
#include <sys/unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <csignal>
#include <ctime>
#include <atomic>
#include <fcntl.h>
#include <errno.h>

#include "../include/ThreadPool.h"
#include "../include/Router.h"
#include "../include/HTTPRequest.h"
#include "../include/HTTPResponse.h"
#include "../include/AppDispatcher.h"

std::atomic<bool> keepRunning = true;

// Colored terminal output
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define RESET   "\033[0m"

std::string staticDir;

// Graceful shutdown handler
void signalHandler(int signum) {
    std::cout << GREEN << "\n[Info] Caught signal " << signum << ", exiting...\n" << RESET;
    keepRunning = false;
}

int main(int argc, char* argv[]) {
    std::signal(SIGINT, signalHandler); // CTRL + c
    std::signal(SIGTERM, signalHandler); // KILL

    // CLI defaults
    int port = 11111;
    int threadCount = 15;
    staticDir = "public";

    // Parse CLI arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "--port" && i + 1 < argc) {
            port = std::stoi(argv[++i]);
        } else if (arg == "--threads" && i + 1 < argc) {
            threadCount = std::stoi(argv[++i]);
        } else if (arg == "--static" && i + 1 < argc) {
            staticDir = argv[++i];
        }
    }

    // Validate CLI input
    if (port <= 0 || port > 65535) {
        std::cerr << RED << "[Error] Invalid port number: " << port << RESET << std::endl;
        return 1;
    }
    if (threadCount <= 0) {
        std::cerr << RED << "[Error] Thread count must be > 0" << RESET << std::endl;
        return 1;
    }

    std::cout << GREEN << "[Info] Server starting on port " << port
            << " with " << threadCount << " threads, serving static from " << staticDir << RESET << "\n";

    // Create server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        std::cerr << RED << "[Error] Couldn't create socket" << RESET << std::endl;
        return 1;
    }

    // Set Socket Level option for immediate restarting
    int opt = 1;
    if(setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        std::cerr << RED << "[Error] setsockopt(SO_REUSEADDR) failed" << RESET << std::endl;
        return 1;
    }

    // Set NON-BLOCKING
    int flags = fcntl(server_socket, F_GETFL, 0);
    // F_GETFL - Get current fd flags
    fcntl(server_socket, F_SETFL, flags | O_NONBLOCK);

    // Bind socket
    sockaddr_in sockAddr{};
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(port);
    sockAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (sockaddr*)&sockAddr, sizeof(sockAddr)) == -1) {
        std::cerr << RED << "[Error] Couldn't bind port to socket" << RESET << std::endl;
        return 1;
    }

    if (listen(server_socket, 10) == -1) {
        std::cerr << RED << "[Error] Couldn't listen to incoming client requests" << RESET << std::endl;
        return 1;
    }

    std::cout << GREEN << "[Info] Listening on port " << port << "..." << RESET << std::endl;

    ThreadPool pool(threadCount);
    Router router;
    AppDispatcher app(router, staticDir);

    // Register Action Handler Endpoints
    router.registerAction("health", [](const std::string&) {
        return R"({"status": "ok", "uptime": "24h"})";
    });

    router.registerAction("version", [](const std::string&) {
        return R"({"app": "LightC++ Server", "version": "1.0.0"})";
    });

    router.registerAction("echo", [](const std::string& body) {
        return "{\"echo\": " + body + "}";
    });

    router.registerAction("time", [](const std::string&) {
        std::time_t now = std::time(nullptr);
        return std::string("{\"time\": \"") + std::ctime(&now) + "\"}";
    });

    router.registerAction("greet", [](const std::string& body) {
        try {
            auto jsonBody = nlohmann::json::parse(body);
            std::string name = jsonBody.value("name", "Guest");
            return std::string(R"({"message": "Hello, )") + name + R"(!"})";
        } catch (...) {
            return std::string(R"({"error": "Invalid JSON"})");
        }
    });


    // Register routes
    router.registerRoute("/health", [](const std::string&) {
        return R"({"status": "ok", "uptime": "24h"})";
    });

    router.registerRoute("/version", [](const std::string&) {
        return R"({"app": "LightC++ Server", "version": "1.0.0"})";
    });

    router.registerRoute("/", [](const std::string& /*body*/) {
        return "Server is running perfectly!";
    });


    // Accept clients
    while (keepRunning) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (sockaddr*)&client_addr, &client_len);
        if (client_socket == -1) {
            // EAGAIN - Try Again, EWOULDBLOCK - Operation would block
            if(errno == EAGAIN || errno == EWOULDBLOCK) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100)); // avoid busy wait
                continue;
            } else {
                std::cerr << RED << "[Error] Couldn't accept client" << RESET << std::endl;
                break;
            }
        }

        pool.enqueueTask([client_socket, &router, &app]() {
            char buffer[4096] = {0};
            int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
            if (bytes_received <= 0) {
                close(client_socket);
                return;
            }

            buffer[bytes_received] = '\0';
            std::string rawRequest(buffer);
            std::cout << "\n======= RECIEVED RESPONSE =======\n" << rawRequest << "\n=====================n";

            HTTPRequest request = HTTPRequest::parse(rawRequest);
            HTTPResponse response = app.HandleRequest(request);

            response.setHeader("X-Powered-By", "C++ Web Server");
            response.setHeader("Server", "LightC++");

            std::string fullResponse = response.to_string();
            std::cout << "\n======= SENT RESPONSE =======\n" << fullResponse << "\n=====================n";

            send(client_socket, fullResponse.c_str(), fullResponse.size(), 0);
            close(client_socket);
        });
    }

    close(server_socket);
    std::cout << GREEN << "[Info] Server shut down cleanly." << RESET << std::endl;
    return 0;
}