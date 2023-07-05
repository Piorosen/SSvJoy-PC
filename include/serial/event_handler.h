#ifndef MAIN_SERIAL_EVENT_H
#define MAIN_SERIAL_EVENT_H

#include <functional>
#include <string>

#include "event/user_access.h"

struct event_handler { 
    std::function<void(std::string)> raw;
    std::function<void()> error;
    std::function<void(user_access)> user_access;
};

#endif // MAIN_SERIAL_EVENT_H