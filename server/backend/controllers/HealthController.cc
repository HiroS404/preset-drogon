#include <drogon/HttpController.h>

using namespace drogon;

class HealthController : public HttpController<HealthController>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HealthController::health, "/api/health", Get);
    METHOD_LIST_END

    void health(const HttpRequestPtr &req,
            std::function<void (const HttpResponsePtr &)> &&callback)
{
    Json::Value json;
    json["status"] = "ok";
    json["message"] = "API is healthy 🚀";

    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
};