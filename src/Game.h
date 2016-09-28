#ifndef GAME_H
#define GAME_H

#include "EventQueue.h"
#include "Map.h"
#include "LockTable.h"
#include "Puzzle.h"
#include "types.h"
#include <vector>


typedef std::vector<Actor *> actors_t ;
typedef std::map<puzzle_t, Puzzle *> puzzlesMap_t;

// This is a top level game class. It's a composite of everything one needs to run the game,
// but with no hardware dependence so we can test it in the cloud.

class Game {
    private:
        Puzzle *puzzle;        // Last puzzle code players entered.

    public:
        hunger_t globalHunger;
        EventQueue events;
        Map map;
        actors_t actors;
        millis_t time;              // Current time (ms)
        game_state_t state;
        strpair_t displayMsg;
        puzzlesMap_t puzzlesMap;

        // Dirty is set when the game state changes (eg: actors move) and
        // cleared when the state is displayed to the player.
        bool dirty;

        virtual void start(print_f print, millis_t _time, hunger_t hunger = 0);  // Starts the game
        void tick(print_f print, millis_t time);            // Runs one tick of game time.
        void scheduleOffsetEvent(millis_t offset, Event *); // Schedules event, offset from now.
        void runEvent(Event *);                             // Schedules to run immediately.
        bool isLocked(const room_t src, const room_t dst);  // Is that door locked?

        void processInput(print_f, const std::string *);
};

#endif
