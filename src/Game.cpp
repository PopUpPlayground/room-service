#include "Game.h"
#include "Actor.h"
#include "LockEvent.h"
#include "HungerEvent.h"

void Game::start(print_f print, millis_t _time, hunger_t startingHunger) {
    time = _time;   // Record game start time. :)
    globalHunger = startingHunger;

    // Make sure the initial game state will be shown to players.
    dirty = true;

    print("Scheduling hunger...\n");
    events.scheduleEvent(0, new HungerEvent);

    print("Activating actors...\n");
    for (actors_t::iterator i = actors.begin(); i != actors.end(); ++i) {

        Event *event = (*i)->recomputeGoal(print, &map, globalHunger);

        if (event != NULL) {
            print("Scheduling goal...");
            
            // Each actor takes at least their speed to get started.
            events.scheduleEvent(time + (*i)->speed, event);

            print("DONE!\n");
        }
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

void Game::processInput(const std::string *input) {
    
    // Whatever we do, it's probably going to dirty things up. :)
    dirty = true;

    if (state == WAIT_PUZZLE) {
        // TODO: Check puzzle is valid.
        puzzle = *input;
        state = WAIT_CODE;
    }
    else if (state == WAIT_CODE) {
        // TODO: Check door code is valid!
        runEvent(new LockEvent(input, puzzle));
        puzzle = "";
        state = WAIT_PUZZLE;
    }

}
