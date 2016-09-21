#ifndef TYPES_H
#define TYPES_H

// As returned by the millis() function.
typedef unsigned long millis_t;

// Waiting time at each room.
typedef unsigned long wait_t;

// A function prototype that's used for printing messages to the game runner.
typedef void (*print_f)(const char *);

// Room numbers.
typedef unsigned int room_t;

// Hunger
typedef unsigned int hunger_t;

#endif
