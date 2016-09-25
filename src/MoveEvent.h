#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include "Event.h"

class Actor;

class MoveEvent : public Event {
    private:
        Actor *actor;

    public:
        MoveEvent(Actor *_actor) : actor(_actor) { };
        void processEvent(print_f, Game *);
};

#endif
