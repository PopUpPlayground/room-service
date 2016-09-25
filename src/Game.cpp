#include "Game.h"
#include "Actor.h"

void Game::start(print_f print, millis_t _time) {
    time = _time;   // Record game start time. :)

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
