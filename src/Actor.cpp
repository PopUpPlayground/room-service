#include "Actor.h"
#include "Game.h"
#include <string>
#include "GoalEvent.h"
#include "MoveEvent.h"

Event *Actor::recomputeGoal(print_f print, Map *map, const hunger_t hunger) {

    print("Finding goal for ");
    print(name);

    assert(map != NULL);

    // The +1 here is so we never divide by zero!
    hunger_t hungerRoll = (rand() % (hunger+1));

    Goals *goalTable = regularGoals;

    if (hungerRoll > hungerBreak) {
        print(" (HUNGRY!)");
        goalTable = hungryGoals;
    }
    print("\n");
    
    // Release previous path if exists
    path.clear();
    
    // Find a place to go.
    // print("...looking for some place to go.\n");
    destination = goalTable->findGoal(room);

    // Find out how to get there.
    // print("...looking for a way to get there.\n");
    bool pathFound = map->findPath(room, destination->room, &path);

    if (!pathFound) {
        // Can't get there, schedule next event to be a recompute.
        // print("...no path found; sleeping instead.\n");
        destination = NULL;
        return new GoalEvent(this);
    }

    // Aww yis, we're heading somewhere. Schedule a move.
    // print("...path found, scheduling move.\n");
    return new MoveEvent(this);
}

void Actor::showPath(print_f print) {
    print("Path for ");
    print(name);

    if (path.empty()) {
        print(": No path defined\n");
        return;
    }

    print(" ");

    char buf[10];
    for (path_t::const_iterator i = path.begin(); i != path.end(); i++) {
        snprintf(buf,10,"%d ",*i);
        print(buf);
    }

    print("\n");
}
