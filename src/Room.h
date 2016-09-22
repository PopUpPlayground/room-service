#ifndef ROOM_H
#define ROOM_H

#include "types.h"
#include "Portal.h"
#include <map>

typedef std::map<room_t, Portal> exits_t;

class Room {
    public:
        const char *name;
        exits_t exits;

        Room(const char *_name) :name(_name) { } ;
};

#endif
