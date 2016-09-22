#ifndef DOORPORTAL_H
#define DOORPORTAL_H

#include "Portal.h"
#include "Room.h"
#include "types.h"

class DoorPortal : public Portal {
    public:
        void trigger(print_f, Actor *, const Room *);
};

#endif
