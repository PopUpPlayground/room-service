#include "Map.h"
#include <assert.h>
#include <set>
#include <algorithm>
#include <limits.h>
#include <queue>
#include "StairPortal.h"
#include "DoorPortal.h"

// DEBUGGING
#include <iostream>
#include "Debug.h"

// Debugging
void Map::dumpVector(path_t *vector) {
    for (path_t::const_iterator i = vector->begin(); i != vector->end(); i++) {
        Debug(*i);
        Debug(" ");
    }
    Debug("\n");
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

    // Our algorithm goes like this:
    // - Push all adjacent rooms with ourselves as the breadcrumb trail onto the queue
    // - While we can pull things off the queue
    // - - Add ourselves to the breadcrumbs of what we just pulled off
    // - - If we're at our destination, stop and return the breadcrumbs
    // - - Otherwise, add all adjacent rooms not in the breadcrumbs to the queue
    // - If we run out of places to search, the destination is unreachable.

    typedef std::pair<path_t *, room_t> pathRoomPair_t;
    std::queue<pathRoomPair_t> queue;

    // Initial seeding of queue
    for (exits_t::const_iterator i = map[src]->exits.begin(); i != map[src]->exits.end(); ++i) {
        queue.push(std::make_pair(new path_t(src), i->first));
    }

    // Main search
    while (! queue.empty() ) {
        pathRoomPair_t candidate = queue.front();
        queue.pop();

        path_t *breadcrumbs = candidate.first;
        const room_t room = candidate.second;

        // Add ourselves to the breadcrumbs.
        breadcrumbs->push_back(room);

        // If we've found our destination.
        if (room == dst) {

            Debug("Route found to ");
            Debug(dst);
            Debug("\n");

            // Remove the starting room from breadcrumbs. It's there to stop us
            // backtracking, and is not part of the route.
            breadcrumbs->erase(breadcrumbs->begin());

            dumpVector(breadcrumbs);

            Debug("Cleaning memory\n");

            // Clean up all memory in the queue that we allocated.
            while (! queue.empty() ) {
                delete queue.front().first;
                queue.pop();
            }

            Debug("Returning route\n");

            // Return our path!
            return breadcrumbs;
        }

        // Find all the exits from here, ignored ones we've already seen.
        for (exits_t::const_iterator i = map[room]->exits.begin(); i != map[room]->exits.end(); ++i) {

            const room_t adjRoom = i->first;

            Debug("Contemplating new room :");
            Debug(adjRoom);
            Debug("\n");

            // If we haven't already been there.
            if (std::find(breadcrumbs->begin(), breadcrumbs->end(), adjRoom) == breadcrumbs->end()) {

                // Create a new breadcrumbs trail. We've already added ourselves above.
                Debug("Creating new path\n");
                path_t *path = new path_t(*breadcrumbs);
                dumpVector(path);
                
                // Add onto the queue
                Debug("Pushing room\n");
                queue.push(std::make_pair(path, adjRoom));
            }
        }

        // Clean up the breadcrumbs for the room we've just popped
        Debug("Deleting breadcrumbs\n");
        delete breadcrumbs;
    }

    // If we're here, then the queue is empty. No memory clean-up required, but we can't
    // find a route either.

    return NULL;
}
