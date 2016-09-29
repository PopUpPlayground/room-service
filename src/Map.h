#ifndef MAP_H
#define MAP_H

#include "Room.h"
#include "LockTable.h"
#include <map>
#include <vector>
#include <string>

class Puzzle;

// The map is just an association between room numbers and rooms.
typedef std::map<room_t, Room *> map_t;

// Paths are used by the pathfinder.
typedef std::vector<path_t *> paths_t;

// It would be great if we had a single map for this, but hey
// deadlines, so we get tech debt instead. Sorry future me.
typedef std::map<const code_t, Room *> roomCodes_t;
typedef std::map<const code_t, Portal *> portalCodes_t;
typedef std::multimap<const code_t, Room *> floorRooms_t;

// The map of the hotel, or whatever space we're putting the players in. :)

class Map {
    private:

        // We keep track of which rooms are on each floor
        floorRooms_t floorRooms;

        // TODO: Remove if not needed.
        // std::multimap<floor_t, DoorPortal *> floorDoors;

        // The map needs to know what's locked.

        void dumpVector(path_t *vector);
        void releasePaths(paths_t *paths);
        bool isDeadEnd(const room_t considered, const room_t dst);

    public:
        roomCodes_t roomCodes;
        portalCodes_t portalCodes;

        // Probably better private
        LockTable locks;

        // Errors from map creation.
        std::string errors;

        map_t map;
        bool findPath(const room_t src, const room_t dst, path_t *out, print_f print);
        bool isLocked(const room_t src, const room_t dst);
        bool isLocked(const room_t src, const Room *dst);

        bool lockDoor(const code_t code, Puzzle *puzzle, const bool emergency = false);
        bool lockRoom(const code_t code, Puzzle *puzzle, codeVector_t *out);
        bool lockFloor(const code_t code, Puzzle *puzzle, codeVector_t *out);

        void unlockDoor(const code_t code, Puzzle *puzzle);

        void newRoom(const char *name, const room_t number, const code_t floor, const char *code = NULL, const led_t led = -1);
        void newBiDoor(const room_t r1, const room_t r2, const char *code = NULL, const led_t led = -1, const bool emergencyOnly = false);
        void newStair(const room_t r1, const room_t r2);
        led_t getPortalLed(std::string code);

        bool validRoom(const room_t room);
        void addError(const char *);

        ~Map() {
            for (map_t::iterator i = map.begin(); i != map.end(); ++i) {
                delete i->second;
            }
            // TODO: Delete floorRooms and floorDoors 
        }

};

#endif
