#include "Game.h"
#include "Actor.h"

void Game::start(print_f print, millis_t _time) {
    time = _time;   // Record game start time. :)
    for (actors_t::iterator i = actors.begin(); i != actors.end(); ++i) {
        Event *event = (*i)->recomputeGoal(&map);
        
        // Each actor takes at least their speed to get started.
        events.scheduleEvent(time + (*i)->speed, event);
    }
}
