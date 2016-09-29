#include "Map.h"
#include <assert.h>
#include <set>
#include <algorithm>
#include <limits.h>
#include <queue>
#include <string.h>
#include "StairPortal.h"
#include "DoorPortal.h"
#include "Puzzle.h"

// DEBUGGING
#include <iostream>
#include "Debug.h"

// Debugging
void Map::dumpVector(path_t *vector) {

#ifdef DEBUG

    for (path_t::const_iterator i = vector->begin(); i != vector->end(); i++) {
        Debug(*i);
        Debug(" ");
    }
    Debug("\n");

#endif

}

// Walks through all our candidates and deletes them. Isn't memory
// management great?
void Map::releasePaths(paths_t *paths) {
    for (paths_t::iterator i = paths->begin(); i != paths->end(); ++i) {
        delete *i;
    }
}

// Map creation
void Map::newRoom(const char *name, const room_t number, const code_t floor, const char *code, const led_t led) {
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
void Map::newBiDoor(const room_t r1, const room_t r2, const char *code, const led_t led, const bool emergencyOnly) {

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
    map[r1]->exits[r2] = new DoorPortal(code,led,emergencyOnly);
    map[r2]->exits[r1] = new DoorPortal(code,led,emergencyOnly);

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
bool Map::lockDoor(const code_t code, Puzzle *puzzle, const bool emergency) {

    portalCodes_t::iterator it = portalCodes.find(code);

    if (it == portalCodes.end()) {
        // Not a valid code.
        return false;
    }

    if (it->second->isEmergencyOnly() && !emergency) {
        // Emergency code not used
        return false;
    }

    // Lock the door!
    locks.addLock(code, puzzle);
    puzzle->used = true;
    return true;
}

void Map::unlockDoor(const code_t code, Puzzle *puzzle) {
    locks.rmLock(code,puzzle);
}

// Returns true if any work done, and adds a list of door codes that have been locked
// to *out.
bool Map::lockRoom(const code_t code, Puzzle *puzzle, codeVector_t *out) {

    assert(out != NULL);

    // Locking a room requires walking through all the lockable exits and
    // locking them.  We return a list of door codes locked.
    
    // See if this is a valid room code.
    roomCodes_t::iterator room_it = roomCodes.find(code);

    // Not found.
    if (room_it == roomCodes.end()) {
        return false;
    }

    // Find all the exits to that room.
    exits_t exits = room_it->second->exits;

    bool anyLocked = false;

    // Walk through them, locking the lockable ones.
    for (exits_t::iterator it = exits.begin(); it != exits.end(); ++it) {
        if (it->second->isLockable()) {
            code_t doorCode = it->second->getCode();
            if (lockDoor(doorCode, puzzle)) {
                out->push_back(doorCode);
                anyLocked = true;
            }
        }
    }

    return anyLocked;
}

bool Map::lockFloor(const code_t code, Puzzle *puzzle, codeVector_t *out) {
    assert(out != NULL);

    bool anyLocked = false;

    std::pair<floorRooms_t::iterator, floorRooms_t::iterator> range = floorRooms.equal_range(code);

    for (floorRooms_t::iterator it = range.first; it != range.second; ++it) {
        const char *roomCode = it->second->code;

        if (roomCode != NULL) {
            anyLocked = lockRoom(roomCode, puzzle, out) || anyLocked;
        }
    }

    return anyLocked;
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

// Returns true if the room is a dead end and *not* our destination.
bool Map::isDeadEnd(const room_t considered, const room_t dst) {
    if (considered == dst) {
        return false;
    }

    // I don't know how we'd get a room with less than one exit, but it's
    // definitely a dead-end.
    return map[considered]->exits.size() <= 1;
}

// Finds a path from src to dst, and writes it to the object provided
// Returns false if no path found.
bool Map::findPath(const room_t src, const room_t dst, path_t *out, print_f print) {
    assert(src != dst);

    // Our algorithm goes like this:
    // - Push all adjacent unlocked rooms with ourselves as the breadcrumb trail onto the queue
    // - While we can pull things off the queue
    // - - Add ourselves to the breadcrumbs of what we just pulled off
    // - - If we're at our destination, stop and return the breadcrumbs
    // - - Otherwise, add all adjacent rooms not *already seen* to the queue.
    // - If we run out of places to search, the destination is unreachable.

    typedef std::pair<path_t *, room_t> pathRoomPair_t;
    std::queue<pathRoomPair_t> queue;

    // There's got to be something faster than this, right?
    std::vector<room_t> seen;

    // Initial seeding of queue
    const exits_t *exits = &(map[src]->exits);
    for (exits_t::const_iterator i = exits->begin(); i != exits->end(); ++i) {

        // Only add *unlocked* paths to our initial seeds.
        if ( ! isLocked(src, i->first) ) {
            // We create a need breadcrumb seed for each possible route.
            // Don't worry, we clean these up later on.
            path_t *seed = new path_t;
            seed->push_back(src);

            // We've seen our source room.
            seen.push_back(src);

            // Add to our queue the seeded path and our new exit.
            queue.push(std::make_pair(seed, i->first));
        }
    }


    // Main search
    while (! queue.empty() ) {

        // char buf[20];
        // snprintf(buf,20,"Queue length: %d\n", (int) queue.size());
        // print(buf);

        pathRoomPair_t candidate = queue.front();
        queue.pop();

        path_t *breadcrumbs = candidate.first;
        const room_t room = candidate.second;

        // Add ourselves to the breadcrumbs and seen list.
        breadcrumbs->push_back(room);
        seen.push_back(room);

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

            // This should copy, right?
            *out = *breadcrumbs;

            // Because if not, we're in trouble. ;)
            delete breadcrumbs;

            return true;
        }

        // Find all the exits from here, ignored ones we've already seen.
        for (exits_t::const_iterator i = map[room]->exits.begin(); i != map[room]->exits.end(); ++i) {

            const room_t adjRoom = i->first;

            Debug("Contemplating new room :");
            Debug(adjRoom);
            Debug("\n");

            // If it's not a dead end, not locked,  haven't already been there,
            // and it doesn't look like we're heading off in a ludicrous route.

            if (
                    ( ! isDeadEnd(adjRoom, dst) )
                    &&
                    ( ! isLocked(room, adjRoom) )
                    &&
                    (std::find(seen.begin(), seen.end(), adjRoom) == seen.end())
                    &&
                    breadcrumbs->size() < MAX_PATH_LENGTH
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

    return false;
}
