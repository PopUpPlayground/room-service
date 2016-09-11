#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

// The heart and soul of our system. We look through this each tick to see
// what events should fire.

#include <map>

#include "Event.h"
#include "types.h"

typedef std::multimap<millis_t, Event *> events_t;

class EventQueue {
    private:
        events_t events;

    public:
        void runEvents(print_f stream, millis_t time);
        void scheduleEvent(millis_t time, Event *event);
};

#endif
