#ifndef MSGEVENT_H
#define MSGEVENT_H

#include "Event.h"
#include "Game.h"
#include <string>

class MsgEvent : public Event {
    private:
        std::string msg;

    public:
        MsgEvent(const char *str) : msg(str) { };
        MsgEvent(const std::string str) : msg(str) { };
        bool processEvent(print_f print, Game *);
};

#endif
