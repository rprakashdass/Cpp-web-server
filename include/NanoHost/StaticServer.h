#ifndef STATICSERVER_H
#define STATICSERVER_H

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "HTTPResponse.h"

class StaticServer {
public:
    static HTTPResponse serve(const std::string& path);
    void setStaticDir(const std::string& path);
private:
    static std::string rootDir;
};

#endif