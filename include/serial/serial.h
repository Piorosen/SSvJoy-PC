#ifndef MAIN_SERIAL_SERIAL_H
#define MAIN_SERIAL_SERIAL_H

#include <serialib.h>
#include <string>
#include <queue>
#include <tuple>

class serial { 
private:
    int baudrate;
    std::string com;
    serialib lib;
public:
    char open(int baudrate, std::string com);
    void close();

    void read();
    int write(std::string);
    int write(unsigned char*, int);
};

#endif // MAIN_SERIAL_SERIAL_H