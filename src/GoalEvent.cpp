#include "GoalEvent.h"
#include "Game.h"
#include "Actor.h"

void GoalEvent::processEvent(print_f print, Game *game) {
    // print("GoalEvent triggered...\n");
    Event *event = actor->recomputeGoal(print, &(game->map), game->globalHunger);

    // If we get an event back, then schedule it with the actor's
    // speed in the future.
    if (event != NULL) {
        // print("Scheduling new goal.\n");
        game->events.scheduleEvent(game->time + actor->speed, event);
    }
}
