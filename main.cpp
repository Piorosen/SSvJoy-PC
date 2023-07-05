#include <drogon/drogon.h>
#include <thread>

using namespace drogon;

int main(int argc, char** argv){ 
    app().setLogPath("./")
         .setLogLevel(trantor::Logger::kWarn)
         .addListener("0.0.0.0", 80)
         .setThreadNum(std::thread::hardware_concurrency())
        //  .enableRunAsDaemon()
         .run();

    return 0;
}   