#ifndef MAIN_SERIAL_EVENT_USER_ACCESS_H
#define MAIN_SERIAL_EVENT_USER_ACCESS_H

#include <string>

struct user_access { 
    bool failure;
    std::string user_name;
    std::string user_id;
};

#endif // MAIN_SERIAL_EVENT_USER_ACCESS_H