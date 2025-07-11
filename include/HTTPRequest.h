#ifndef ROUTER_H
#define ROUTER_H

#include <string>
#include <sstream>
#include <algorithm> // remove methode
#include <unordered_map>

class HTTPRequest {
private:
public:
    std::string method;
    std::string path;
    std::string body;
    std::unordered_map<std::string, std::string> headers;

    // static methodes need not to be initialized
    static HTTPRequest parse(const std::string&);
};

#endif