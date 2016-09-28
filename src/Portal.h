#ifndef PORTAL_H
#define PORTAL_H

#include "types.h"
#include "LockTable.h"
#include <stdio.h>

// These are things baddies can move through. They're doorways, windows, etc.
// They don't have sources or destinations, since the rooms have this.

class Room; // Forward declaration
class Actor;
class Game;

class Portal {
    public:

        // The LED, if there is one.
        const led_t led;

        // This needs to be filled by the derived class. For most things it
        // will just move the actor, or have them re-path if locked.
        virtual void trigger(print_f print, Actor *actor, const Room *dst, Game *) = 0;

        // Only some doors can be locked. By default they're not.
        virtual bool isLocked(LockTable *) { return false; } 

        Portal(const led_t _led = -1) :led(_led) { };
        virtual ~Portal() { };

    protected:
        void moveActor(print_f print, Actor *actor, const Room *dst);
};

#endif
