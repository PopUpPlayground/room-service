#include "Map.h"
#include <assert.h>
#include <set>
#include <algorithm>
#include <limits.h>
#include <queue>
#include <string.h>
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
void Map::newRoom(const char *name, const room_t number, const floor_t floor, const char *code, const led_t led) {
    assert(name != NULL);

    if (map.find(number) != map.end()) {
        // OMG, they're adding a room that already exists! Bail out now.
        errors += "Attempt to double-add room number ";
        errors += number;
        errors += "\n";
        return;
    }

    if (code != NULL && roomCodes.find(code) != roomCodes.end()) {
        // They've given us a code that's already been used. Nope.
        errors += "Attempt to double-add room code ";
        errors += code;
        errors += "\n";
        return;
    }

    Room *room = new Room(name, number, code, led);

    // Add the room to our map.
    map[number] = room;

    // Add it to the floor index.
    floorRooms.insert(std::make_pair(floor,room));

    // Add it to our code list, if we have one.
    if (code != NULL) {
        roomCodes[code] = room;
    }
}

// Stairs don't have identifiers, and can't be locked or manipulated
// by the players.
void Map::newStair(const room_t r1, const room_t r2) {
    map[r1]->exits[r2] = new StairPortal();
    map[r2]->exits[r1] = new StairPortal();
}

// Bi-directional door creation. Rooms must exist first.
// TODO: Add to door/floor table
void Map::newBiDoor(const room_t r1, const room_t r2, const char *code, const led_t led) {

    if (map.find(r1) == map.end()) {
        errors += "Attempt to make BiDoor from void room ";
        errors += r1;
        errors += "\n";
        return;
    }

    if (map.find(r2) == map.end())  {
        errors += "Attempt to make BiDoor to void room ";
        errors += r2;
        errors += "\n";
        return;
    }

    if (code != NULL && portalCodes.find(code) != portalCodes.end()) {
        errors += "Attempt to re-use portal code ";
        errors += code;
        errors += "\n";
        return;
    }
    
    // The doors are different objects in memory, but share the same ID,
    // and hence the same locks.
    map[r1]->exits[r2] = new DoorPortal(code,led);
    map[r2]->exits[r1] = new DoorPortal(code,led);

    if (code != NULL) {
        portalCodes[code] = map[r1]->exits[r2];
    }
}

bool Map::isLocked(const room_t src, const room_t dst) {
    Portal *portal = map[src]->exits[dst];

    // We should never see a null portal, but if we do, then
    // hey, that path is *definitely* locked.
    if (portal == NULL) {
        Debug("Null portal in Map::isLocked\n");
        return true;
    }

    return portal->isLocked(&locks);
}

bool Map::isLocked(const room_t src, const Room *dst) {
    return isLocked(src, dst->number);
}

// Returns true if request was valid, false otherwise.
bool Map::lockDoor(const code_t code, const puzzle_t puzzle) {

    if (portalCodes.find(code) == portalCodes.end()) {
        return false;
    }

    locks.addLock(code, puzzle);
    return true;
}

void Map::unlockDoor(const code_t code, const puzzle_t puzzle) {
    locks.rmLock(code,puzzle);
}

// Returns the LED number, but only if we're given a door.
led_t Map::getPortalLed(std::string code) {

    if (portalCodes.find(code) == portalCodes.end()) {
        return NO_LED;
    }

    return portalCodes.at(code)->led;
}

bool Map::validRoom(const room_t room) {
    if (map.find(room) == map.end()) {
        return false;
    }
    return true;
}

void Map::addError(const char *msg) {
    errors += msg;
}

// Finds a path from src to dst, and returns a pointer to it.
// It's the responsibility of the caller to clean that up when done.
path_t *Map::findPath(const room_t src, const room_t dst) {
    assert(src != dst);

    // Our algorithm goes like this:
    // - Push all adjacent unlocked rooms with ourselves as the breadcrumb trail onto the queue
    // - While we can pull things off the queue
    // - - Add ourselves to the breadcrumbs of what we just pulled off
    // - - If we're at our destination, stop and return the breadcrumbs
    // - - Otherwise, add all adjacent rooms not in the breadcrumbs to the queue
    // - If we run out of places to search, the destination is unreachable.

    typedef std::pair<path_t *, room_t> pathRoomPair_t;
    std::queue<pathRoomPair_t> queue;

    // Initial seeding of queue
    const exits_t *exits = &(map[src]->exits);
    for (exits_t::const_iterator i = exits->begin(); i != exits->end(); ++i) {

        // Only add *unlocked* paths to our initial seeds.
        if ( ! isLocked(src, i->first) ) {
            // We create a need breadcrumb seed for each possible route.
            // Don't worry, we clean these up later on.
            path_t *seed = new path_t;
            seed->push_back(src);

            // Add to our queue the seeded path and our new exit.
            queue.push(std::make_pair(seed, i->first));
        }
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

            // If it's not locked, and we haven't already been there.
            if (
                    ( ! isLocked(room, adjRoom) )
                    &&
                    std::find(breadcrumbs->begin(), breadcrumbs->end(), adjRoom) == breadcrumbs->end()
            ) {

                // Create a new breadcrumbs trail. We've already added ourselves above.
                Debug("Creating new path from ");
                dumpVector(breadcrumbs);
                path_t *path = new path_t(*breadcrumbs);
                Debug("New path is ");
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
