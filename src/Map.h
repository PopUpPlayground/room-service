#ifndef MAP_H
#define MAP_H

#include "Room.h"

// The map is just an association between room numbers and rooms.
typedef std::map<room_t, Room *> map_t;
typedef std::vector<path_t *> paths_t;

// The map of the hotel. We use an edge-centric design.

class Map {
    private:
        void dumpVector(path_t *vector);
        void releasePaths(paths_t *paths);

    public:
        map_t map;
        path_t *findPath(const room_t src, const room_t dst, const path_t *baseRoute);
        void newRoom(const char *name, const room_t number);
        void newBiDoor(const room_t r1, const room_t r2, const ident_t id);

        ~Map() {
            for (map_t::iterator i = map.begin(); i != map.end(); ++i) {
                delete i->second;
            }
        }

};

#endif
