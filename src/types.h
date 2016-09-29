#ifndef TYPES_H
#define TYPES_H

#include <vector>
#include <string>

#define NO_LED -1

// Pathfinding and other things can chew a lot of memory. We can
// limit that to an extent here.
#define MAX_PATH_LENGTH 20

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
typedef std::vector<code_t> codeVector_t;

// Puzzle codes entered by players.
typedef std::string puzzle_t;

// A path is a vector of rooms.
typedef std::vector<room_t> path_t;

// LEDs as addressed by our drivers. This *must* be signed, as -1 is used as
// "no LED".
typedef int led_t;

typedef std::pair<std::string, std::string> strpair_t;

enum game_state_t { WAIT_PUZZLE, WAIT_CODE, DISPLAY_MSG };

// Lock types for puzzles.
enum lock_type_t { DOOR, ROOM, FLOOR, EMERGENCY };

#endif
