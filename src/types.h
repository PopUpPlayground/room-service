#ifndef TYPES_H
#define TYPES_H

#define MAX_CODE_LENGTH 16

#include <vector>
#include <string>

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

// Identifiers as used internally by the game.
typedef int ident_t;
typedef ident_t floor_t;
typedef ident_t room_t;
typedef ident_t door_t;

// Codes as used by players, both for objects (doors, floors, etc)
typedef std::string code_t;

// Puzzle codes entered by players.
typedef std::string puzzle_t;

// A path is a vector of rooms.
typedef std::vector<room_t> path_t;

// LEDs as addressed by our drivers. This *must* be signed, as -1 is used as
// "no LED".
typedef int led_t;

typedef std::pair<std::string, std::string> strpair_t;

enum game_state_t { WAIT_PUZZLE, WAIT_CODE, DISPLAY_MSG };

#endif
