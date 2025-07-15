#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

class HTTPRequest {
private:
public:
    std::string version;
    std::string method;
    std::string status;
    std::string path;
    std::string body;
    std::unordered_map<std::string, std::string> headers;

    // static methodes need not to be initialized
    static HTTPRequest parse(const std::string& rawRequest);
};

#endif