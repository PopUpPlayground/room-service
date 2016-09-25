#include "GoalEvent.h"
#include "Game.h"
#include "Actor.h"

void GoalEvent::processEvent(print_f print, Game *game) {
    Event *event = actor->recomputeGoal(print, &(game->map));

    // If we get an event back, then schedule it with the actor's
    // speed in the future.
    if (event != NULL) {
        game->events.scheduleEvent(game->time + actor->speed, event);
    }
}
