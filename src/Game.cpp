#include "Game.h"
#include "Actor.h"

void Game::start(print_f print, millis_t _time) {
    time = _time;   // Record game start time. :)

    // Make sure the initial game state will be shown to players.
    dirty = true;

    print("Activating actors...\n");
    for (actors_t::iterator i = actors.begin(); i != actors.end(); ++i) {

        Event *event = (*i)->recomputeGoal(print, &map);

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

void Game::processInput(const std::string *input) {
    
    // Whatever we do, it's probably going to dirty things up. :)
    dirty = true;

    if (state == WAIT_PUZZLE) {
        // TODO: Copy code.
        state = WAIT_CODE;
    }
    else if (state == WAIT_CODE) {
        // TODO: Process pair!
        state = WAIT_PUZZLE;
    }

}
