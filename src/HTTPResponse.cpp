#include <NanoHost/HTTPResponse.h>

std::string HTTPResponse::getMimeType(const std::string& filePath) {
    static const std::unordered_map<std::string, std::string> mimeTypes = {
        { ".html", "text/html" },
        { ".htm",  "text/html" },
        { ".css",  "text/css" },
        { ".js",   "application/javascript" },
        { ".json", "application/json" },
        { ".png",  "image/png" },
        { ".jpg",  "image/jpeg" },
        { ".jpeg", "image/jpeg" },
        { ".gif",  "image/gif" },
        { ".svg",  "image/svg+xml" },
        { ".ico",  "image/x-icon" },
        { ".txt",  "text/plain" },
        { ".pdf",  "application/pdf" },
        { ".wasm", "application/wasm" },
        { ".xml",  "application/xml" },
    };

    size_t dotPos = filePath.rfind('.');
    if (dotPos != std::string::npos) {
        std::string ext = filePath.substr(dotPos);
        auto it = mimeTypes.find(ext);
        if (it != mimeTypes.end()) {
            return it->second;
        }
    }

    return "application/octet-stream";  // default for unknown types
}


const std::unordered_map<int, std::string> HTTPResponse::statusMessages = {
    {200, "OK"}, {201, "Created"}, {204, "No Content"},
    {400, "Bad Request"}, {401, "Unauthorized"}, {403, "Forbidden"},
    {404, "Not Found"}, {405, "Method Not Allowed"},
    {500, "Internal Server Error"}, {502, "Bad Gateway"}, {503, "Service Unavailable"}
};

HTTPResponse::HTTPResponse(int code, std::string body, std::string contentType)
    : statusCode(code), body(std::move(body)) {
    auto it = statusMessages.find(code);
    statusMessage = (it != statusMessages.end()) ? it->second : "Unknown Status";
    headers["Content-Type"] = contentType;
    headers["Content-Length"] = std::to_string(this->body.length());
    headers["Connection"] = "keep-alive";
}

std::string HTTPResponse::getStatusMessage() const {
    return statusMessage;
}

int HTTPResponse::getStatusCode() const {
    return statusCode;
}

void HTTPResponse::setHeader(const std::string& key, const std::string& value) {
    headers[key] = value;
}

std::string HTTPResponse::to_string() const {
    std::ostringstream oss;
    oss << "HTTP/1.1 " << statusCode << " " << statusMessage << "\r\n";
    for (const auto& [key, value] : headers) {
        oss << key << ": " << value << "\r\n";
    }
    oss << "\r\n" << body;
    return oss.str();
}

HTTPResponse HTTPResponse::ok(int code, const std::string& body) {
    if (code < 200 || code >= 300) {
        throw std::invalid_argument("ok() must be used with a 2xx status code.");
    }
    return HTTPResponse(code, body);
}

HTTPResponse HTTPResponse::error(int code, const std::string& message) {
    if (code < 400 || code >= 600) {
        throw std::invalid_argument("error() must be used with a 4xx or 5xx status code.");
    }
    return HTTPResponse(code, message);
}