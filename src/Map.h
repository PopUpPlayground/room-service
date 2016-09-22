#ifndef MAP_H
#define MAP_H

#include "Room.h"

// The map is just an association between room numbers and rooms.
typedef std::map<roomNumber_t, Room *> map_t;

// The map of the hotel. We use an edge-centric design.

#endif
