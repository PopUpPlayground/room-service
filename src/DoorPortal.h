#ifndef DOORPORTAL_H
#define DOORPORTAL_H

#include "Portal.h"
#include "types.h"

class DoorPortal : public Portal {
    public:

        const char *code;   // Code used by players. Can be null.
        const led_t led;    // LED number. Can be -1 for none.

        // Doors are only lockable if they have a code.
        bool isLocked(LockTable *);
        void trigger(print_f, Actor *, const Room *, Game *);

        DoorPortal(const char *_code, const led_t _led = -1) 
            :code(_code), led(_led) { };
};

#endif
