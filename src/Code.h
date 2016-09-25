#ifndef CODE_H
#define CODE_H

#include "types.h"

// Code class. Codes are entered by the players, and can only
// be used once.

class Code {
    public:
        // We don't have the actual code itself, as that goes in
        // the big code table of everything which we'll have.

        // Simple flags for what types of objects our code can
        // lock. Usually only *one* of these will be true, so a
        // player doesn't try to use a code on the wrong object type
        // (wasting a room lock on a single door, etc)
        const bool doorLock;
        const bool roomLock;
        const bool floorLock;

        // How long do we lock for?
        const millis_t duration;
        
        // How much load does this add?
        const load_t systemLoad;

        // Applies the code, returning true if successful.
        bool apply(DoorPortal);
        bool apply(Room);
        bool apply(Floor);

        // TODO: Have canApply methods?

    private:
        // Has this code been used already?
        // Private, because this can only flip to true, and
        // never back.
        bool used = false;
};

#endif
