#ifndef STAIRPORTAL_H
#define STAIRPORtAL_H

#include "Portal.h"
#include "types.h"

// Stairs can't be locked, and always allow movement.
class StairPortal : public Portal {
    public:
        void trigger(print_f print, Actor *actor, const Room *room) {
            moveActor(print, actor, room);
        }
};

#endif
