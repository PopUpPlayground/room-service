#ifndef GAME_H
#define GAME_H

#include "EventQueue.h"
#include "Map.h"
#include "LockTable.h"
#include "Puzzle.h"
#include "types.h"
#include "Actor.h"
#include <vector>

class PlayerHaxxedEvent;

typedef std::vector<Actor *> actors_t ;
typedef std::vector<PlayerHaxxedEvent *> haxxVector_t;
typedef std::map<puzzle_t, Puzzle *> puzzlesMap_t;
typedef std::vector<std::pair<millis_t, std::string> > msgVector_t;

// This is a top level game class. It's a composite of everything one needs to run the game,
// but with no hardware dependence so we can test it in the cloud.

class Game {
    public:
        hunger_t globalHunger;
        EventQueue events;
        Map map;
        actors_t actors;
        millis_t time;              // Current time (ms)
        game_state_t state;
        strpair_t displayMsg;
        puzzlesMap_t puzzlesMap;
        msgVector_t msgVector;            // Scheduled messages to run during game.
        haxxVector_t haxx;
        Puzzle *puzzle;        // Last puzzle code players entered.

        // Dirty is set when the game state changes (eg: actors move) and
        // cleared when the state is displayed to the player.
        bool dirty;

        // Have we just unlocked the player's input? This triggers extra hardware routines.
        bool justUnlocked;

        virtual void start(print_f print, millis_t _time, hunger_t hunger = 0);  // Starts the game
        void tick(print_f print, millis_t time);            // Runs one tick of game time.
        void scheduleOffsetEvent(millis_t offset, Event *); // Schedules event, offset from now.
        void runEvent(Event *);                             // Schedules to run immediately.
        bool isLocked(const room_t src, const room_t dst);  // Is that door locked?

        void lockConsole(std::string line1, std::string line2 = "", millis_t time = 2000);

        void processInput(print_f, const std::string *);

        // Mostly to make valgrind happy

        ~Game() {

            // Clean puzzles from memory.
            for (puzzlesMap_t::iterator it = puzzlesMap.begin(); it != puzzlesMap.end(); ++it) {
                delete it->second;
            }

            // Clean actors
            for (actors_t::iterator it = actors.begin(); it != actors.end(); ++it) {
                delete *it;
            }
        }
};

#endif
