#ifndef DOORPORTAL_H
#define DOORPORTAL_H

#include "Portal.h"
#include "types.h"

class DoorPortal : public Portal {
    public:
        char *trigger(const Actor);
};

#endif
