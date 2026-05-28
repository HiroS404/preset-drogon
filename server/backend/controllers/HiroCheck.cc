#include <drogon/HttpController.h>


using namespace drogon;
class HiroCheck : public HttpController<HiroCheck>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(HiroCheck::check, "/api/hirocheck", Get);
    METHOD_LIST_END

    void check(const HttpRequestPtr &req,
            std::function<void (const HttpResponsePtr &)> &&callback)
{
    Json::Value json;
    json["name"] = "syeempre hiro";
    json["message"] = "HiroCheck is working! 🎉 OMSIMMM";

    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
};