#include <drogon/drogon.h>
#include <thread>
#include <serial/serial.h>
#include <serial/builder.h>

#include <spdlog/spdlog.h>
#include <chrono>

using namespace drogon;

int main(int argc, char** argv){ 
    serial s;
    spdlog::info("open: {}", s.open(115200, "COM4"));
            //                 STX   TYPE  ID  DATA01 02     03   04   CHK   ETX

    app().setLogPath("./")
         .setLogLevel(trantor::Logger::kWarn)
         .addListener("0.0.0.0", 80)
         .setThreadNum(std::thread::hardware_concurrency())
         .registerHandler("/test",
                    [&s](const HttpRequestPtr& req,
                       std::function<void (const HttpResponsePtr &)> &&callback)
                    {
                        auto obj = req->jsonObject();
                        int type = obj->get("type", 0).asInt();
                        int id = obj->get("id", 0).asInt();
                        int value = obj->get("value", 0).asInt();
                        auto data = builder()
                            .setType((Type)type)
                            ->setButtonId((byte)id)
                            ->setValue(value)
                            ->build();
                        
                        s.write(data.data(), data.size());
                        Json::Value json;
                        json["result"] = "ok";
                        json["message"] = s.read();
                        json["body"] = std::string((char*)data.data());

                        auto resp=HttpResponse::newHttpJsonResponse(json);
                        callback(resp);
                    },
                    {Post})
         .run();

    s.close();
    return 0;
}   