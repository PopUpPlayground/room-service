#ifndef MAP_H
#define MAP_H

#include "Room.h"
#include "LockTable.h"
#include <map>
#include <vector>
#include <string>

// The map is just an association between room numbers and rooms.
typedef std::map<room_t, Room *> map_t;

// Paths are used by the pathfinder.
typedef std::vector<path_t *> paths_t;

// It would be great if we had a single map for this, but hey
// deadlines, so we get tech debt instead. Sorry future me.
typedef std::map<const code_t, Room *> roomCodes_t;
typedef std::map<const code_t, Portal *> portalCodes_t;

// The map of the hotel, or whatever space we're putting the players in. :)

class Map {
    private:

        // We keep track of which rooms and doors are on each floor.
        // TODO: Actually implement these.
        std::multimap<floor_t, Room *> floorRooms;
        std::multimap<floor_t, DoorPortal *> floorDoors;

        roomCodes_t roomCodes;
        portalCodes_t portalCodes;

        // The map needs to know what's locked.

        void dumpVector(path_t *vector);
        void releasePaths(paths_t *paths);

    public:
        // Probably better private
        LockTable locks;

        // Errors from map creation.
        std::string errors;

        map_t map;
        path_t *findPath(const room_t src, const room_t dst);
        bool isLocked(const room_t src, const room_t dst);
        bool isLocked(const room_t src, const Room *dst);

        bool lockDoor(const code_t code, const puzzle_t puzzle);
        void unlockDoor(const code_t code, const puzzle_t puzzle);

        void newRoom(const char *name, const room_t number, const floor_t floor, const char *code = NULL, const led_t led = -1);
        void newBiDoor(const room_t r1, const room_t r2, const char *code = NULL, const led_t led = -1);
        void newStair(const room_t r1, const room_t r2);
        led_t getPortalLed(std::string code);

        ~Map() {
            for (map_t::iterator i = map.begin(); i != map.end(); ++i) {
                delete i->second;
            }
            // TODO: Delete floorRooms and floorDoors 
        }

};

#endif
