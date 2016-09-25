#include "Actor.h"
#include "Map.h"
#include <string>

std::string Actor::recomputeGoal(Map *map) {
    assert(map != NULL);

    std::string ret = "";
    
    // TODO: Hungry check!
    
    // Release previous path if exists
    if (path != NULL) {
        delete path;
    }
    
    // Find a place to go.
    const Destination *dst = regularGoals->findGoal(room);

    // Find out how to get there.
    path = map->findPath(room, dst->room);

    if (path == NULL) {

        // TODO: Schedule our rest.

        ret = name;
        ret += " has nowhere to go, and takes a rest.\n";
        return ret;
    }

    // Otherwise, schedule a move to that room.
    
    return ret;
}
