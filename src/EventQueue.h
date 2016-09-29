#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

// The heart and soul of our system. We look through this each tick to see
// what events should fire.

#include <map>

#include "Event.h"
#include "types.h"

class Game;
typedef std::multimap<millis_t, Event *> events_t;

class EventQueue {
    private:
        events_t events;

        events_t::iterator fireEvent(print_f, Game *, events_t::iterator);

    public:
        void runEvents(print_f stream, millis_t time, Game *game);
        void scheduleEvent(millis_t time, Event *event);
        void clearLocks(print_f, Game *);
        void clearUnlockConsoleEvents();
};

#endif
