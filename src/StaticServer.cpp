#include "../include/StaticServer.h"

std::string StaticServer::rootDir = "";

void StaticServer::setStaticDir(const std::string& path) {
    rootDir = path;
}

HTTPResponse StaticServer::serve(const std::string& path) {
    std::string filePath = StaticServer::rootDir + path;
    if (filePath.back() == '/')
        filePath += "index.html";

    if (!std::filesystem::exists(filePath)) {
        return HTTPResponse(404, "404 Not Found");
    }

    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return HTTPResponse(500, "500 Internal Server Error");
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // load file into buffer as string

    std::string mimeType = HTTPResponse::getMimeType(filePath);
    return HTTPResponse(200, buffer.str(), mimeType);
}