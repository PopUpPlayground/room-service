#include "Actor.h"
#include "Game.h"
#include <string>
#include "GoalEvent.h"
#include "MoveEvent.h"

Event *Actor::pathTo(print_f print, Map *map, const Destination *dest) {
    // Release previous path if exists
    path.clear();

    // Find out how to get there.
    // print("...looking for a way to get there.\n");
    // print("Starting pathfinder...\n");
    bool pathFound = map->findPath(room, dest->room, &path, print);
    // print("...done\n");

    if (!pathFound) {
        // Can't get there, schedule next event to be a recompute.
        // print("...no path found; sleeping instead.\n");
        destination = NULL;
        return &goalEvent;
    }

    // Aww yis, we're heading somewhere. Schedule a move.
    // print("...path found, scheduling move.\n");

    destination = dest;
    return &moveEvent;
}

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
    
    // Find a place to go.
    // print("...looking for some place to go.\n");

    // Find a goal and path to it.
    return pathTo(print, map, goalTable->findGoal(room));
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
