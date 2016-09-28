#ifndef ACTOR_H
#define ACTOR_H

#include "types.h"
#include "Goals.h"
#include "Map.h"
#include <string>

class Game;
class Event;

typedef unsigned int speed_t;

// Usually baddies, but could be anything. :)
class Actor {
    public:
        const char *name;
        const speed_t speed;
        const millis_t activateTime;

        room_t room;

        // Hungry hungry!
        const hunger_t hungerBreak;

        Goals *regularGoals;
        Goals *hungryGoals;

        // Path to wherever we're going.
        path_t path;
        const Destination *destination;

        Event *recomputeGoal(print_f, Map *, const hunger_t);
        void showPath(print_f);
        
        Actor(
            const char *_name, const speed_t _speed, const room_t starting_room,
            const hunger_t _hungerBreak,
            Goals *_regularGoals, Goals *_hungryGoals, const millis_t _activateTime = 0
        )
            : name(_name)
            , speed(_speed)
            , activateTime(_activateTime)
            , room(starting_room)
            , hungerBreak(_hungerBreak)
            , regularGoals(_regularGoals)
            , hungryGoals(_hungryGoals)
            { }
            
};

#endif
