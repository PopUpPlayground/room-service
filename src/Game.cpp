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

    switch (state) {
        case WAIT_PUZZLE: {
            puzzlesMap_t::iterator it = puzzlesMap.find(*input);
            if (it != puzzlesMap.end()) {

                if (it->second->used) {
                    lockConsole("Code already", "used...");
                }
                else {
                    // Code valid, change to waiting for room.
                    puzzle = it->second;
                    state = WAIT_CODE;
                }
            }
            else {
                lockConsole("Invalid code");
            }
            break;
        }
        case WAIT_CODE: {

            // Switch back to waiting for puzzle input; may be overriden
            // by lockConsole later in the switch.
            state = WAIT_PUZZLE;

            switch(puzzle->type) {
                case DOOR: {
                    if ( map.lockDoor(*input,puzzle) ) {
                        // Successful lock! Schedule unlock
                        lockConsole("Door locked","",1000);
                        scheduleOffsetEvent(puzzle->duration, new UnlockEvent(*input,puzzle));
                    }
                    else {
                        lockConsole("Door code","not valid");
                    }
                    break;
                }
                case ROOM: {
                    codeVector_t codes;
                    if ( map.lockRoom(*input,puzzle,&codes) ) {
                        lockConsole("Room locked","",1000);

                        for(codeVector_t::iterator code = codes.begin(); code != codes.end(); ++code) {
                            scheduleOffsetEvent(puzzle->duration, new UnlockEvent(*code,puzzle));
                        }
                    }
                    else {
                        lockConsole("Room code","not valid");
                    }
                    break;
                }

                case FLOOR: {
                    codeVector_t codes;
                    if ( map.lockFloor(*input,puzzle,&codes) ) {
                        lockConsole("Floor lockdown","enabled",5000);

                        for(codeVector_t::iterator code = codes.begin(); code != codes.end(); ++code) {
                            scheduleOffsetEvent(puzzle->duration, new UnlockEvent(*code,puzzle));
                        }
                    }
                    else {
                        lockConsole("Floor code","not valid");
                    }

                    break;
                }

                case EMERGENCY:
                    break;
            }

            // Regardless of locks, reset our puzle.
            puzzle = NULL;
        }
    }
}

void Game::lockConsole(std::string line1, std::string line2, millis_t time) {
    static UnlockConsoleEvent unlock;
    state = DISPLAY_MSG;
    displayMsg = std::make_pair(line1,line2);
    scheduleOffsetEvent(time, &unlock);
}
