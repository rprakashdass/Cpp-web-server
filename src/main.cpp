#include <iostream>
#include <sys/unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>

#include "../include/ThreadPool.h"

const u_int PORT = 8080;

int main() {
    // create server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket == -1) {
        std::cerr << "[Error] Couldn't create socket\n";
        return 1;
    }

    // Bind socket to port 8080
    sockaddr_in sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(PORT);
    sockAddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(server_socket, (sockaddr*)&sockAddr, sizeof(sockAddr)) == -1) {
        std::cerr << "[Error] Couldn't bind port to socket\n";
        return 1;
    }

    // Listen to incoming client requests
    if(listen(server_socket, 10) == -1) {
        std::cerr << "[Error] Couldn't listen to incoming client requests\n";
        return 1;
    }

    std::cout << "Server listening on port 8080..." << std::endl;

    // Threadpool implementation
    ThreadPool pool(15);

    while(true) {
        socklen_t client_len = sizeof(sockAddr);
        int client_socket = accept(server_socket, (sockaddr*)&sockAddr, &client_len);
        if (client_socket == -1) {
            std::cerr << "[Error] Couldn't accept client\n";
            continue;
        }

        pool.enqueueTask([client_socket]() {
            char buffer[1024] = {0};
            int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
            if (bytes_received > 0) {
                buffer[bytes_received] = '\0';
                std::cout << "Received request:\n" << buffer << std::endl;
            }

            const char* response =
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Content-Length: 12\r\n"
                "Connection: close\r\n"
                "\r\n"
                "Hello World\n";

            send(client_socket, response, strlen(response), 0);
            close(client_socket);
        });
    }

    return 0;
}