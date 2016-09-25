#include "Actor.h"
#include "Game.h"
#include <string>
#include "GoalEvent.h"
#include "MoveEvent.h"

Event *Actor::recomputeGoal(Map *map) {
    assert(map != NULL);

    std::string ret = "";
    
    // TODO: Hungry check!
    
    // Release previous path if exists
    if (path != NULL) {
        delete path;
    }
    
    // Find a place to go.
    destination = regularGoals->findGoal(room);

    // Find out how to get there.
    path = map->findPath(room, destination->room);

    if (path == NULL) {
        // Can't get there, schedule next event to be a recompute.
        destination = NULL;
        return new GoalEvent(this);
    }

    // Aww yis, we're heading somewhere. Schedule a move.
    return new MoveEvent(this);
}
