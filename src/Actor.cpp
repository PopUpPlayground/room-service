#include "Actor.h"
#include "Game.h"
#include <string>
#include "GoalEvent.h"
#include "MsgEvent.h"

Event *Actor::recomputeGoal(Map *map) {
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
        // Can't get there, schedule next event to be a recompute.
        return new GoalEvent(this, map);
    }

    // Otherwise, schedule a move to that room.
    // XXX - Not a message event; this is a stub
    return new MsgEvent("XXX FILL ME IN");
}
