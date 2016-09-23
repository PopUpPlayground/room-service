#ifndef GOALS_H
#define GOALS_H

#include <vector>
#include "types.h"

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
        ) : weight(_weight), room(_room), wait(_wait), sigma(_sigma) { };
};

typedef std::vector<Destination *> Destinations;

// Goals tables for actors. Right now these are just locations to which
// they'd like to move.

class Goals {
    public:

        // Default constructor
        Goals() {
            totalWeightings = 0;
        };

        // Destructor
        ~Goals() {
            // XXX: Walk through all elements and delete them first!
        };

        // Add a goal
        void add(const room_t room, const weight_t weight, const wait_t wait, const wait_t sigma) {
            destinations.push_back(
                new Destination(room, weight, wait, sigma)
            );

            totalWeightings += weight;
        }

    private:
        Destinations destinations;
        unsigned int totalWeightings;

};

#endif
