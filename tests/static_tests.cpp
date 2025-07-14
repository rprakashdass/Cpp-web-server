#include <StaticServer.h>
#include <cassert>
#include <string>

int main() {
    StaticServer staticServer;
    staticServer.setStaticDir("public");
    auto resp = StaticServer::serve("/index.html");
    std::string out = resp.to_string();
    // Should contain HTTP 200 and some HTML
    assert(out.find("200 OK") != std::string::npos);
    assert(out.find("<html") != std::string::npos);
    return 0;
} 