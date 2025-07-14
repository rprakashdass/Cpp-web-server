#include <StaticServer.h>

std::string StaticServer::rootDir = "";

#include <iostream>
void StaticServer::setStaticDir(const std::string& path) {
    rootDir = path;
}


HTTPResponse StaticServer::serve(const std::string& path) {
    std::string filePath = StaticServer::rootDir + path;

    if (filePath.back() == '/')
        filePath += "index.html";

    std::cout << "[StaticServer] Looking for: " << filePath << std::endl;

    if (!std::filesystem::exists(filePath)) {
        std::cout << "[StaticServer] File not found: " << filePath << std::endl;
        return HTTPResponse(404, "404 Not Found");
    }

    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        std::cout << "[StaticServer] File exists but couldn't open: " << filePath << std::endl;
        return HTTPResponse(500, "500 Internal Server Error");
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string mimeType = HTTPResponse::getMimeType(filePath);
    return HTTPResponse(200, buffer.str(), mimeType);
}