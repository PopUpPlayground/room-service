#ifndef ROOM_H
#define ROOM_H

#include "types.h"
#include "Portal.h"
#include <map>

typedef std::map<room_t, Portal> exits_t;

class Room {
    public:
        const char *name;
        const room_t number;
        exits_t exits;

        Room(const char *_name, const room_t _number) :name(_name), number(_number) { } ;
};

#endif
