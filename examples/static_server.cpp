#include <AppDispatcher.h>
#include <Router.h>
#include <StaticServer.h>

int main() {
    Router router;
    AppDispatcher app(router);
    StaticServer staticServer;
    staticServer.setStaticDir("public");
    // Add more routes or actions as needed
    // ...
    // See src/server.cpp for full server loop
    return 0;
}  