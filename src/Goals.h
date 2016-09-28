#ifndef GOALS_H
#define GOALS_H

#include <vector>
#include <stdlib.h>
#include "types.h"
#include <assert.h>
#include "Map.h"

// Struct that defines each goal.
class Destination {
    public:
        const room_t room;
        const weight_t weight;
        const wait_t wait;          // In milliseconds
        const wait_t sigma;         // In milliseconds

        Destination(
            const room_t _room,
            const weight_t _weight,
            const wait_t _wait,
            const wait_t _sigma
        ) : room(_room), weight(_weight), wait(_wait), sigma(_sigma) { };
};

typedef std::vector<Destination *> Destinations;

// Goals tables for actors. Right now these are just locations to which
// they'd like to move.

class Goals {
    private:
        Map *map;

    public:

        // Default constructor
        Goals(Map *_map) :map(_map), totalWeightings(0)  { };

        // Destructor
        ~Goals() {
            // XXX: Walk through all elements and delete them first!
        };

        void add(const room_t room, const weight_t weight, const wait_t wait, const wait_t sigma);
        const Destination* findGoal(const room_t currentRoom);

    private:
        Destinations destinations;
        weight_t totalWeightings;

        const Destination* pickRoom();
};

#endif
