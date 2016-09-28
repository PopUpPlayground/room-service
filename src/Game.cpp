#include "Game.h"
#include "Actor.h"
#include "HungerEvent.h"
#include "GoalEvent.h"
#include "UnlockEvent.h"
#include "UnlockConsoleEvent.h"

void Game::start(print_f print, millis_t _time, hunger_t startingHunger) {
    time = _time;   // Record game start time. :)
    globalHunger = startingHunger;

    // Make sure the initial game state will be shown to players.
    dirty = true;

    print("Scheduling hunger...\n");
    events.scheduleEvent(0, new HungerEvent);

    // Actors are now activated in the child's start method, since they'll
    // come into play based upon the game.

    print("Scheduling actor wake-ups...\n");
    for (actors_t::iterator i = actors.begin(); i != actors.end(); ++i) {
        scheduleOffsetEvent((*i)->activateTime, new GoalEvent(*i));
    }
}

void Game::tick(print_f print, millis_t _time) {
    time = _time;
    events.runEvents(print, time, this);
}

void Game::scheduleOffsetEvent(millis_t offset, Event *event) {
    events.scheduleEvent(time + offset, event);
}

// This just schedules it to run immediately.
void Game::runEvent(Event *event) {
    events.scheduleEvent(time, event);
}

void Game::processInput(print_f print, const std::string *input) {
    
    // Whatever we do, it's probably going to dirty things up. :)
    dirty = true;

    if (state == WAIT_PUZZLE) {
        puzzlesMap_t::iterator it = puzzlesMap.find(*input);
        if (it != puzzlesMap.end()) {

            if (it->second->used) {
                print("Code already used\n");
                lockConsole("Code already", "used...");
                return;
            }
            else {
                puzzle = it->second;
                state = WAIT_CODE;
                return;
            }
        }
        else {
            print("Invalid code\n");
            lockConsole("Invalid code");
            return;
        }
    }
    else if (state == WAIT_CODE) {

        if (puzzle->type == DOOR) {
            if ( map.lockDoor(*input,puzzle) ) {
                // Successful lock! Schedule unlock
                print("Locking door\n");
                scheduleOffsetEvent(puzzle->duration, new UnlockEvent(*input,puzzle));
            }
            else {
                print("Door lock unsuccessful\n");
                // Unsuccessful.
            }
        }
        
        puzzle = NULL;
        state = WAIT_PUZZLE;
    }

    // You gave us a code when we weren't expecting it? Hah.

}

void Game::lockConsole(std::string line1, std::string line2, millis_t time) {
    state = DISPLAY_MSG;
    displayMsg = std::make_pair(line1,line2);
    scheduleOffsetEvent(time, new UnlockConsoleEvent);
}
