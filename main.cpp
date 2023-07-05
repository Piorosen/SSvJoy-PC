#include <drogon/drogon.h>
#include <thread>
#include <serial/serial.h>
#include <serial/builder.h>

#include <spdlog/spdlog.h>
#include <chrono>
#include <cxxopts.hpp>

using namespace drogon;

int main(int argc, char** argv){ 
    cxxopts::Options options("SSvJoy", "HTTP 통신으로 당신의 조이스틱을 제어합니다.");
    options.add_options()
        ("c,com", "Com Port", cxxopts::value<std::string>())
        ("b,baudrate", "Baud Rate", cxxopts::value<int>()->default_value("115200"))
        ;
    serial s;
    try { 
        auto result = options.parse(argc, argv);
        spdlog::info("open: {}", s.open(result["baudrate"].as<int>(), result["com"].as<std::string>()));
    }catch (std::exception e) { 
        spdlog::error("{}", e.what());
        spdlog::error("{}", options.help());
        return 0;
    }    

            //                 STX   TYPE  ID  DATA01 02     03   04   CHK   ETX

    app().setLogPath("./")
         .setLogLevel(trantor::Logger::kWarn)
         .addListener("0.0.0.0", 80)
         .setThreadNum(1) // 단일 쓰레드로 통해, 데이터 오류 발생을 최소화함.
         .registerHandler("/serial",
                    [&s](const HttpRequestPtr& req,
                       std::function<void (const HttpResponsePtr &)> &&callback)
                    {
                        spdlog::info("{}", req->body());
                        
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
                        
                        spdlog::info("{}", json.toStyledString());
                        auto resp=HttpResponse::newHttpJsonResponse(json);
                        callback(resp);
                    },
                    {Post})
         .run();

    s.close();
    return 0;
}   