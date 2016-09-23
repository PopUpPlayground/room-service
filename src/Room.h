#ifndef ROOM_H
#define ROOM_H

#include "types.h"
#include "DoorPortal.h"
#include <map>

// TODO: This is supposed to be of type Portal, so we can have things other
// than doors. But my C++ isn't good enough to figure out what the compiler
// is complaining about, and if we have an un-pure virtual Portal class then it ends
// up getting called which is wrong.
typedef std::map<room_t, DoorPortal *> exits_t;

class Room {
    public:
        const char *name;
        const room_t number;
        exits_t exits;

        Room(const char *_name, const room_t _number) :name(_name), number(_number) { } ;
};

#endif
