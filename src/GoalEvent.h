#ifndef GOALEVENT_H
#define GOALEVENT_H

#include "Event.h"
#include "types.h"

class Map;
class Game;
class Actor;

// Causes an actor to recompute their goal
class GoalEvent : public Event {
    private:
        Actor *actor;

    public:
        GoalEvent(Actor *_actor) : actor(_actor) { };
        bool processEvent(print_f print, Game *);
};

#endif
