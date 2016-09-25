#ifndef GOALEVENT_H
#define GOALEVENT_H

#include "Event.h"
#include <string>

class Map;
class Game;
class Actor;

// Causes an actor to recompute their goal
class GoalEvent : public Event {
    private:
        Actor *actor;
        Map *map;

    public:
        GoalEvent(Actor *_actor, Map *_map) : actor(_actor), map(_map) { };
        std::string processEvent(Game *);
};

#endif
