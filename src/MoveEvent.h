#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include "Event.h"
#include <string>

class Actor;

class MoveEvent : public Event {
    private:
        Actor *actor;

    public:
        MoveEvent(Actor *_actor) : actor(_actor) { };
        std::string processEvent(Game *);
};

#endif
