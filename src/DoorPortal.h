#ifndef DOORPORTAL_H
#define DOORPORTAL_H

#include "Portal.h"
#include "types.h"

class DoorPortal : public Portal {
    public:
        ident_t number; // Should be const, but crying at compile errors right now.
        void trigger(print_f, Actor *, const Room *);

        DoorPortal(ident_t _number) :number(_number) { };
};

#endif
