#ifndef MSGEVENT_H
#define MSGEVENT_H

#include "Event.h"
#include <string>

class MsgEvent : public Event {
    private:
        std::string msg;

    public:
        MsgEvent(const char *str) : msg(str) { };
        std::string processEvent();
};

#endif
