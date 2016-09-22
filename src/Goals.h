#ifndef GOALS_H
#define GOALS_H

// Struct that defines each goal.
struct Destination {
    const unsigned int weight;
    const room_t room;
    const wait_t wait;          // In milliseconds
    const wait_t sigma;         // In milliseconds
};

// Goals tables for actors. Right now these are just locations to which
// they'd like to move.

class Goals {
    public:
        const Destination destinations[];

    private:
        const unsigned int totalWeightings;

};

#endif
