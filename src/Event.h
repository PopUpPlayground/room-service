#ifndef EVENT_H
#define EVENT_H

#include <string>

// Forward declare
class Game;

// A virtual class for various event types.

class Event {
    public:

        // This event gets called when it's time to handle something.
        // The string gets displayed to the game runner.
        virtual std::string processEvent(Game *) = 0;

        // This is how we let child classes manage deletion, yes?
        virtual ~Event() { }
};

#endif
