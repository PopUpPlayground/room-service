#ifndef EVENT_H
#define EVENT_H

#include "types.h"

// Forward declare
class Game;

// A virtual class for various event types.

class Event {
    public:

        // This event gets called when it's time to handle something.
        // Returns TRUE if we should free the event's memory.
        // (a lot of events will re-use themselves).
        virtual bool processEvent(print_f print, Game *) = 0;
        virtual bool isUnlockEvent() { return false; }

        // This is how we let child classes manage deletion, yes?
        virtual ~Event() { }
};

#endif
