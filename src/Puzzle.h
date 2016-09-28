#ifndef PUZZLE_H
#define PUZZLE_H

#include "types.h"

// Code class. Codes are entered by the players, and can only
// be used once.

class Puzzle {
    public:
        // We don't have the actual code itself, as that goes in
        // the big code table of everything which we'll have.

        // What type of code (door, floor, etc)
        const lock_type_t type;

        // How long do we lock for?
        const millis_t duration;
        
        // How much load does this add? (Currently unused)
        // const load_t systemLoad;

        // Has this code been used already?
        bool used;

        Puzzle(lock_type_t _type, millis_t _duration = 60 * 1000) 
            : type(_type)
            , duration(_duration)
            , used(false)
        { }
};

#endif
