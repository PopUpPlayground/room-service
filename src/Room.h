#ifndef ROOM_H
#define ROOM_H

#include "types.h"
#include "DoorPortal.h"
#include <map>

typedef std::map<room_t, Portal *> exits_t;

class Room {
    public:
        const char *name;       // Human readable name
        const char *code;       // Player code. Can be null
        const room_t number;    // Internal room number
        exits_t exits;          // Exits to other rooms.

        Room(const char *_name, const room_t _number, const char *_code = NULL)
            :name(_name), code(_code), number(_number) { } ;

        ~Room() {
            // Clears all door memory.
            
            for (exits_t::iterator i = exits.begin(); i != exits.end(); ++i) {
                delete i->second;
            }
        }
};

#endif
