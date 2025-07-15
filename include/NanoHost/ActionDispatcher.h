#include "Router.h"
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "nlohmann/json.hpp"

class ActionDispatcher {
public:
    using json = nlohmann::json;
    ActionDispatcher(Router& r);
    HTTPResponse dispatch(const HTTPRequest& request);
private:
    Router& router;
};
