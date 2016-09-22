#ifndef PORTAL_H
#define PORTAL_H

#include "types.h"
#include "Actor.h"
#include <stdio.h>

// These are things baddies can move through. They're doorways, windows, etc.
// They don't have sources or destinations, since the rooms have this.

class Portal {
    public:
        // This needs to be filled by the derived class. For most things it
        // will just move the actor, or have them re-path if locked.
        virtual char *trigger(const Actor, const room_t dst) { return NULL; };
};

#endif
