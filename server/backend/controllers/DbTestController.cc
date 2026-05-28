#include <drogon/HttpController.h>
#include <drogon/drogon.h>

using namespace drogon;

class DbTestController : public drogon::HttpController<DbTestController>
{
    public:
        METHOD_LIST_BEGIN
        ADD_METHOD_TO(DbTestController::testDb, "/api/dbtest", Get);
        METHOD_LIST_END

        // Changed callback to an rvalue reference (&&)
        void testDb(
            const HttpRequestPtr& req, 
            std::function<void (const HttpResponsePtr &)> &&callback) 
        {
            auto dbClient = drogon::app().getDbClient();

            // We use std::move to pass ownership into the async handlers
            // Because there are two lambdas, we copy to a shared variable first 
            // or let the first capture copy it, and the second move it.
            auto sharedCallback = std::move(callback);

            dbClient->execSqlAsync(
                "SELECT 1", 
                [sharedCallback](const drogon::orm::Result& result){
                    Json::Value json;
                    json["status"] = "success";
                    json["message"] = "Database connection successful! 🎉 OMSIMMM";
                    auto resp = HttpResponse::newHttpJsonResponse(json);
                    sharedCallback(resp);
                },
                [sharedCallback](const drogon::orm::DrogonDbException& e){
                    Json::Value json;
                    json["status"] = "error";
                    json["message"] = e.base().what();
                    auto resp = HttpResponse::newHttpJsonResponse(json);
                    sharedCallback(resp);
                 });
        }
};