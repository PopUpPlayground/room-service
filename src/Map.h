#ifndef MAP_H
#define MAP_H

#include "Room.h"
#include <assert.h>
#include <set>
#include <algorithm>
#include <limits.h>

// The map is just an association between room numbers and rooms.
typedef std::map<room_t, Room *> map_t;
typedef std::vector<path_t *> paths_t;

// The map of the hotel. We use an edge-centric design.

class Map {
    private:
        void releasePaths(paths_t *paths) {
            for (paths_t::iterator i = paths->begin(); i != paths->end();) {
                if (*i == NULL) {
                    ++i;
                    continue;
                }

                // Magic to let us delete a thing using an iterator, but
                // not one we're currently iterating over.
                paths_t::iterator save = i;
                ++save;
                delete *i;

                // Do we really need to erase this? The caller is going
                // to drop the entire vector when we're done.
                paths->erase(i);
                i = save;
            }
        }

    public:
        map_t map;

        // Yah, there should be heaps of helper functions here to build
        // your map. There isn't yet.

        // Finds a path from src to dst, and returns a pointer to it.
        // It's the responsibility of the caller to clean that up when done.
        
        path_t *findPath(const room_t src, const room_t dst, const path_t *baseRoute) {
            assert(src != dst);

            exits_t exits = map[src]->exits;

            // Yup, it's a breadth first search. We do this every time,
            // because we have lots of CPU. If it becomes slow we can
            // use Dijkstra's algorithm and cache it.
            
            // First of all, if we have a direct path, just use that.
            // TODO: Check if not locked.
            if (exits.find(dst) != exits.end()) {
                return new path_t (dst);
            }

            // Otherwise, we'll walk through all the possible routes and
            // pick the shortest.

            paths_t candidates;

            // Copy our base route, as we're going to add ourselves to it.
            path_t newRoute (*baseRoute);
            newRoute.push_back(src);

            for (exits_t::const_iterator i = exits.begin(); i != exits.end(); ++i) {

                // If we've already got this room on our route, then don't
                // consider entering it.
                // NOTE: This is O(N^2). Sorry.
                if (std::find(baseRoute->begin(), baseRoute->end(), i->first) != baseRoute->end()) {
                    continue;
                }

                // Otherwise, find a route to our destination using this path.
                candidates.push_back(
                    findPath( i->first, dst, &newRoute)
                );
            }

            // We now have a list of candidates, pick the shortest.
            unsigned int shortestLength = INT_MAX;
            path_t *shortestPath;
            for (paths_t::const_iterator i = candidates.begin(); i != candidates.end(); ++i) {

                // Skip null elements
                if (*i == NULL) continue;

                if ((*i)->size() < shortestLength) {
                    shortestLength = (*i)->size();
                    shortestPath = *i;
                }
            }

            // There is no way to get to there from here.
            if (shortestPath == NULL) {
                releasePaths(&candidates);
                return NULL;
            }

            // Hooray! We have a winner! Return it for great justice!
            
            // Copy the path into a non-volatile object.
            path_t *returnPath = new path_t (*shortestPath);

            // Clean all the memory we were using.
            releasePaths(&candidates);

            // Rejoice and return
            return returnPath;
        }

};

#endif
