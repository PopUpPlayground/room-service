#include "Map.h"
#include <assert.h>
#include <set>
#include <algorithm>
#include <limits.h>
#include "StairPortal.h"
#include "DoorPortal.h"

// DEBUGGING
#include <iostream>

// Debugging
void Map::dumpVector(path_t *vector) {
    std::cerr << "*** Returning route: ";
    for (path_t::const_iterator i = vector->begin(); i != vector->end(); i++) {
        std::cerr << *i << " ";
    }
    std::cerr << "*** \n\n\n";
}

// Walks through all our candidates and deletes them. Isn't memory
// management great?
void Map::releasePaths(paths_t *paths) {
    for (paths_t::iterator i = paths->begin(); i != paths->end(); ++i) {
        delete *i;
    }
}

// Map creation
void Map::newRoom(const char *name, const room_t number, const floor_t floor, const char *code){
    assert(name != NULL);

    // We're just trusting you not to add a room twice, okay?

    Room *room = new Room(name, number, code);
    map[number] = room;
    floorRooms.insert(std::make_pair(floor,room));
}

// Stairs don't have identifiers, and can't be locked or manipulated
// by the players.
void Map::newStair(const room_t r1, const room_t r2) {
    map[r1]->exits[r2] = new StairPortal();
    map[r2]->exits[r1] = new StairPortal();
}

// Bi-directional door creation. Rooms must exist first.
// TODO: Add to door/floor table
// TODO: Doors which don't have lockable doodads
void Map::newBiDoor(const room_t r1, const room_t r2, const char *code) {
    
    // The doors are different objects in memory, but share the same ID,
    // and hence the same locks.
    map[r1]->exits[r2] = new DoorPortal(code);
    map[r2]->exits[r1] = new DoorPortal(code);
}

// Finds a path from src to dst, and returns a pointer to it.
// It's the responsibility of the caller to clean that up when done.
path_t *Map::findPath(const room_t src, const room_t dst, const path_t *baseRoute) {
    assert(src != dst);

    exits_t exits = map[src]->exits;

    // Yup, it's a breadth first search. We do this every time,
    // because we have lots of CPU. If it becomes slow we can
    // use Dijkstra's algorithm and cache it.

    path_t newRoute;
    
    // Copy our base route over, if we had one.
    if (baseRoute != NULL) {
        newRoute = *baseRoute;
    }
    else {
        std::cerr << "\n+++ Starting new pathfinder to " << dst << " +++\n";
    }
    
    // First of all, if we have a direct path, just use that.
    // TODO: Check if not locked.
    if (exits.find(dst) != exits.end()) {
        std::cerr << "Simple route found to " << dst << "\n";

        path_t *returnRoute = new path_t (newRoute);
        returnRoute->push_back(src);
        returnRoute->push_back(dst);
        dumpVector(returnRoute);
        return returnRoute;
    }

    std::cerr << "No simple route exists to " << dst << ", looking harder.\n";

    // Otherwise, we'll walk through all the possible routes and
    // pick the shortest.

    paths_t candidates;

    newRoute.push_back(src);

    std::cerr << "Considering options.\n";

    for (exits_t::const_iterator i = exits.begin(); i != exits.end(); ++i) {

        std::cerr << "Conteplating moving to " << i->first << "\n";

        // If we've already got this room on our route, then don't
        // consider entering it.
        // NOTE: This is O(N^2). Sorry.
        if (baseRoute != NULL && std::find(baseRoute->begin(), baseRoute->end(), i->first) != baseRoute->end()) {
            std::cerr << "...but already moved there.\n";
            continue;
        }

        // Otherwise, find a route to our destination using this path.
        std::cerr << "...could work, investigating.\n";

        path_t *possibleRoute = findPath( i->first, dst, &newRoute);

        if (possibleRoute != NULL) {
            std::cerr << "...route found, adding to candidates.\n";
            candidates.push_back(possibleRoute);
        }
        else {
            std::cerr << "...no luck down that path\n";
        }
    }

    if (candidates.size() == 0) {
        std::cerr << "No route exist!\n";
        return NULL;
    }

    std::cerr << "Investigating options for best fit\n";

    // We now have a list of candidates, pick the shortest.
    // We can just use the first element in our candidates list as
    // the shortest thus far.
    unsigned int shortestLength = (*(candidates.begin()))->size();
    path_t *shortestPath = *(candidates.begin());

    for (paths_t::const_iterator i = candidates.begin(); i != candidates.end(); ++i) {

        if ((*i)->size() < shortestLength) {
            shortestLength = (*i)->size();
            shortestPath = *i;
        }
    }

    // Copy the path into a non-volatile object.
    std::cerr << "Route found of length " << shortestLength << ", saving it.\n";
    dumpVector(shortestPath);
    path_t *returnPath = new path_t (*shortestPath);

    // Clean all the memory we were using.
    std::cerr << "Releasing memory\n";
    releasePaths(&candidates);

    // Rejoice and return
    std::cerr << "Returning route\n";
    return returnPath;
}
