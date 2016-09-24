#ifndef TYPES_H
#define TYPES_H

#include <vector>

// As returned by the millis() function.
typedef unsigned long millis_t;

// Waiting time at each room.
typedef unsigned long wait_t;

// A function prototype that's used for printing messages to the game runner.
typedef void (*print_f)(const char *);

// Hunger
typedef unsigned int hunger_t;

// System load type.
typedef unsigned char load_t;

// Weightings for the goals table.
typedef unsigned int weight_t;

// Identifiers as used by the players and map.
// These are room numbers, floor numbers, door numbers, etc.

typedef int ident_t;
typedef ident_t floor_t;
typedef ident_t room_t;
typedef ident_t door_t;

// Value used when a thing cannot be locked.
#define NOLOCK -1

// A path is a vector of rooms.
typedef std::vector<room_t> path_t;

#endif
