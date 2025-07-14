#include <Router.h>
#include <cassert>
#include <string>

int main() {
    Router router;
    bool called = false;
    router.registerRoute("/test", [&](const std::string& body) {
        called = true;
        return std::string("ok:") + body;
    });
    auto resp = router.route("/test", "data");
    assert(called);
    assert(resp.to_string().find("ok:data") != std::string::npos);
    return 0;
} 