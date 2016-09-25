#include "Actor.h"
#include "Game.h"
#include <string>
#include "GoalEvent.h"
#include "MoveEvent.h"

Event *Actor::recomputeGoal(print_f print, Map *map) {

    print("Finding goal for ");
    print(name);
    print("\n");

    assert(map != NULL);

    // TODO: Hungry check!
    
    // Release previous path if exists
    if (path != NULL) {
        print("...Releasing previous goal.\n");
        delete path;
    }
    
    // Find a place to go.
    print("...looking for some place to go.\n");
    destination = regularGoals->findGoal(room);

    // Find out how to get there.
    print("...looking for a way to get there.\n");
    path = map->findPath(room, destination->room);

    if (path == NULL) {
        // Can't get there, schedule next event to be a recompute.
        print("...no path found; sleeping instead.\n");
        destination = NULL;
        return new GoalEvent(this);
    }

    // Aww yis, we're heading somewhere. Schedule a move.
    print("...path found, scheduling move.\n");
    return new MoveEvent(this);
}
