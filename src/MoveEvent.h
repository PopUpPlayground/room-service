#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include "Event.h"

class Actor;

class MoveEvent : public Event {
    private:
        Actor *actor;

    public:
        MoveEvent(Actor *_actor) : actor(_actor) { };
        bool processEvent(print_f, Game *);
};

#endif
