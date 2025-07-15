#include <HTTPRequest.h>
#include <HTTPResponse.h>
#include <cassert>
#include <string>

int main() {
    std::string raw = "GET /hello HTTP/1.1\r\nHost: localhost\r\n\r\n";
    auto req = HTTPRequest::parse(raw);
    assert(req.method == "GET");
    assert(req.path == "/hello");
    assert(req.version == "HTTP/1.1");
    assert(req.headers["Host"] == "localhost");

    auto resp = HTTPResponse::ok(200, "Hello");
    std::string out = resp.to_string();
    assert(out.find("200 OK") != std::string::npos);
    assert(out.find("Hello") != std::string::npos);
    return 0;
}