#include <string>
#include <sstream>
#include <vector>

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

std::string serial::read() { 
    char text[256];
    this->lib.readString(text, '\n', 20, 25);
    spdlog::info(text);
    return std::string(text);
}

int serial::write(std::string data) { 
    return this->lib.writeString(data.c_str());
}

int serial::write(unsigned char* data, int size) { 
    return this->lib.writeBytes(data, size);
}
