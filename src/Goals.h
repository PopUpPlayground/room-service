#ifndef GOALS_H
#define GOALS_H

#include <vector>
#include <stdlib.h>
#include "types.h"
#include <assert.h>

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

        // Given a current location, finds where this actor wants to go next.
        const Destination* findGoal(const room_t currentRoom) {
            const Destination* nextRoom;

            // This just keeps rolling until we get a room that isn't ours.
            while (nextRoom = pickRoom()) {
                if (nextRoom->room != currentRoom) {
                    return nextRoom;
                }
            }

            // Should never, ever reach here.
            assert(false);
        }

    private:
        Destinations destinations;
        weight_t totalWeightings;

        // Picks a room at random (using our weightings) and returns it.
        // Pays no attention to the room we're currently in.
        const Destination* pickRoom() {
            // We create a random number in the range of 1 to totalWeightings
            // (inclusive). We then walk through our table, adding each
            // weighting to our accumulator as we go, it reaches or exceeds our
            // roll at which point we've found our destination.
            //
            // We could do this by decrementing our roll, but we're using
            // unsigned ints, and doing negative there would be bad.
            //
            // This is O(n), and I'm sure an O(1) solution exists, but meh,
            // we've got heaps of CPU.
            
            // This has a small amount of skew, but the players won't notice so
            // we don't care.
            weight_t roll  = 1 + (rand() % totalWeightings);
            weight_t accum = 0;

            for (Destinations::const_iterator i = destinations.begin(); i != destinations.end(); ++i) {

                // Increment our accumulator by the weight of the current room.
                accum += (*i)->weight;

                // If we've reached far enough in our table, return the element.
                if (accum >= roll) {
                    return *i;   // Returns a pointer to the entry we want.
                }
            }

            // You know, we're never supposed to reach here. Something's gone very wrong.
            
            assert(false);
        }


};

#endif
