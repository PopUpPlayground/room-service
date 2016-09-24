#include "Goals.h"

// Add a goal
void Goals::add(const room_t room, const weight_t weight, const wait_t wait, const wait_t sigma) {
    destinations.push_back(
        new Destination(room, weight, wait, sigma)
    );

    totalWeightings += weight;
}

// Given a current location, finds where this actor wants to go next.
const Destination* Goals::findGoal(const room_t currentRoom) {
    const Destination* nextRoom;

    // This just keeps rolling until we get a room that isn't ours.
    while ((nextRoom = pickRoom())) {
        if (nextRoom->room != currentRoom) {
            return nextRoom;
        }
    }

    // Should never, ever reach here.
    assert(false);
}

// Picks a room at random (using our weightings) and returns it.
// Pays no attention to the room we're currently in.
const Destination* Goals::pickRoom() {
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
