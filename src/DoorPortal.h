#ifndef DOORPORTAL_H
#define DOORPORTAL_H

#include "Portal.h"
#include "types.h"

class DoorPortal : public Portal {
    public:

        const char *code;   // Code used by players. Can be null.
        const bool emergencyOnly; // Requires emergency code.

        // Doors are only lockable if they have a code.
        bool isLocked(LockTable *);
        bool isLockable();
        bool isEmergencyOnly() { return emergencyOnly; }
        const char *getCode() { return code; }

        void trigger(print_f, Actor *, const Room *, Game *);

        DoorPortal(const char *_code, const led_t _led = -1, bool emerOnly = false) 
            :Portal(_led), code(_code), emergencyOnly(emerOnly) { };
};

#endif
