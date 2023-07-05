#include <vector>
#include <string>
#include <sstream>

#include <serial/serial.h>
#include <spdlog/spdlog.h>

std::vector<std::string> split(std::string str, char delimiter) {
    std::istringstream iss(str);             // istringstream에 str을 담는다.
    std::string buffer;                      // 구분자를 기준으로 절삭된 문자열이 담겨지는 버퍼
 
    std::vector<std::string> result;
 
    // istringstream은 istream을 상속받으므로 getline을 사용할 수 있다.
    while (std::getline(iss, buffer, delimiter)) {
        result.push_back(buffer);               // 절삭된 문자열을 vector에 저장
    }
 
    return result;
}

char serial::open(int baudrate, std::string com) { 
    this->com = com;
    this->baudrate = baudrate;

    return this->lib.openDevice(com.c_str(), baudrate);
}

void serial::close() { 
    this->lib.closeDevice();
}

void serial::read() { 
    char text[256];
    this->lib.readString(text, '#', 256);

    int i;
    for (i = 0; text[i] != '\0' && text[i - 1] != '$'; i++);

    std::string data = &text[i];
    if (data.length() == 0) { 
        if (this->handler.error) { 
            this->handler.error();
            return;
        }
    }

    if (this->handler.raw) { 
        this->handler.raw(data);
    }

    data.pop_back();

    auto spt = split(data, '@');
    for (const auto& p : spt) {
        spdlog::info("nyanyachacha!, {}", p);
    }

    if (this->handler.user_access && spt.size() == 3) { 
        user_access result;
        if (spt[0] == "true") { 
            result.failure = false;
        }else { 
            result.failure = true;
        }
        result.user_name = spt[1];
        result.user_id = spt[2];
        this->handler.user_access(result);
    }else if (spt.size() != 3){ 
        spdlog::warn("user_access : [{}] size not matching", data);
    }else if (!this->handler.user_access){ 
        spdlog::warn("user_access : handler user access not join");
    }
}

int serial::write(std::string data) { 
    return this->lib.writeString(data.c_str());
}

event_handler* const serial::event() { 
    return &this->handler;
}
