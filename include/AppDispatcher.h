#ifndef APPDISPATCHER_H
#define APPDISPATCHER_H

#include "./ActionDispatcher.h"
#include "./StaticServer.h"
#include "./HTTPRequest.h"

class AppDispatcher {
public:
    AppDispatcher(Router& router);
    HTTPResponse HandleRequest(const HTTPRequest& request);
private:
    Router& router;
    ActionDispatcher actionDispatcher;
};

#endif