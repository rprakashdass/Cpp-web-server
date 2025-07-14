#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <string>
#include <unordered_map>
#include <sstream>

class HTTPResponse {
public:
    HTTPResponse(int code, std::string body, std::string contentType = "text/plain");

    static HTTPResponse ok(int code = 200, const std::string& body = "");
    static HTTPResponse error(int code = 500, const std::string& message = "Internal Server Error");
    static std::string getMimeType(const std::string& filePath);

    std::string to_string() const;
    std::string getStatusMessage() const;
    int getStatusCode() const;
    void setHeader(const std::string& key, const std::string& value);
private:
    int statusCode;
    std::string body;
    std::string statusMessage;
    std::unordered_map<std::string, std::string> headers;

    static const std::unordered_map<int, std::string> statusMessages;
};

#endif