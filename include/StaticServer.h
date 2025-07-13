#ifndef STATICSERVER_H
#define STATICSERVER_H

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "../include/HTTPResponse.h"

class StaticServer {
public:
    explicit StaticServer(const std::string& rootDir);
    HTTPResponse serve(const std::string& path);

private:
    const std::string& rootDir;
};

#endif