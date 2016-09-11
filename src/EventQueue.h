#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

// The heart and soul of our system. We look through this each tick to see
// what events should fire.

#include <map>
#include "Event.h"
#include "types.h"

class EventQueue {
    private:
        std::multimap<millis_t, Event> events;
}

#endif
