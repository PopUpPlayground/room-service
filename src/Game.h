#ifndef GAME_H
#define GAME_H

#include "EventQueue.h"
#include "Map.h"
#include "LockTable.h"
#include <vector>

typedef std::vector<Actor *> actors_t ;

// This is a top level game class. It's a composite of everything one needs to run the game,
// but with no hardware dependence so we can test it in the cloud.

class Game {
    public:
        EventQueue events;
        Map map;
        actors_t actors;
        millis_t time;              // Current time (ms)

        void start(print_f print, millis_t _time);          // Starts the game
        void tick(print_f print, millis_t time);            // Runs one tick of game time.
        void scheduleOffsetEvent(millis_t offset, Event *); // Schedules event, offset from now.
        bool isLocked(const room_t src, const room_t dst);  // Is that door locked?
};

#endif
