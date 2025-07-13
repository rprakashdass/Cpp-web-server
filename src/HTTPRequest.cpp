#include "../include/HTTPRequest.h"

HTTPRequest HTTPRequest::parse(const std::string& rawRequest) {
    HTTPRequest req;

    // osstream for writing string and isstream for viceversa
    std::istringstream iss(rawRequest);
    std::string line;

    // 1. reading from the string "GET /index.html HTTP/1.1"
    std::getline(iss, line);
    std::istringstream firstLine(line);
    std::cout << "[PARSING F_NAME] " << line << std::endl;
    firstLine >> req.method >> req.path >> req.version;
    std::cout << "METH: " << req.method
          << "\nPATH: " << req.path
          << "\nVersion: " << req.version << std::endl;


    // 2. Reading Headers
    // \n is handled by getline
    while(std::getline(iss, line) && line != "\r") {

        size_t colonPos = line.find(":");
        if(colonPos != std::string::npos) {
            std::string header = line.substr(0, colonPos);
            std::string value = line.substr(colonPos+1);

            value.erase(std::remove(value.begin(), value.end(), '\r'), value.end());
            value.erase(0, value.find_first_not_of(" ")); // remove whitespaces

            std::cout << "[ADDING.. HEADER] " << header << " with value " << value << std::endl;
            req.headers[header] = value;
        }
    }

    // 3. Read Body Data
    std::string bodyLine, bodyData;
    while(std::getline(iss, bodyLine)) {
        if(!bodyLine.empty() && bodyData.back() == '\r') {
            bodyLine.pop_back();
        }
        bodyData.append(bodyLine + "\n");
    }

    req.body = bodyData;
    std::cout << "[REQUEST BODY] <=> " << req.body << std::endl;

    return req;
}