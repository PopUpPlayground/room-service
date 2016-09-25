#ifndef DOORPORTAL_H
#define DOORPORTAL_H

#include "Portal.h"
#include "types.h"

class DoorPortal : public Portal {
    public:

        const char *code;   // Code used by players. Can be null.

        // Doors are only lockable if they have a code.
        bool isLocked(LockTable *);
        void trigger(print_f, Actor *, const Room *, Game *);

        DoorPortal(const char *_code) :code(_code) { };
};

#endif
