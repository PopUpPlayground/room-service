#ifndef ACTOR_H
#define ACTOR_H

#include "types.h"
#include "Goals.h"

typedef unsigned int speed_t;

// Usually baddies, but could be anything. :)
class Actor {
    public:
        const char *name;
        const speed_t speed;

        room_t room;

        // Hungry hungry!
        hunger_t hunger;
        const hunger_t hungerBreak;

        const Goals *regularGoals;
        const Goals *hungryGoals;

        // Path to wherever we're going.
        path_t *path;
        
        Actor(
            const char *_name, const speed_t _speed, const room_t starting_room,
            const hunger_t _hungerBreak,
            const Goals *_regularGoals, const Goals *_hungryGoals
        )
            : name(_name)
            , speed(_speed)
            , room(starting_room)
            , hungerBreak(_hungerBreak)
            , regularGoals(_regularGoals)
            , hungryGoals(_hungryGoals)
            { }
            
};

#endif
