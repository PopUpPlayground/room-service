#ifndef UNLOCKCONSOLEEVENT_H
#define UNLOCKCONSOLEEVENT_H

#include "Event.h"
#include "types.h"

class Puzzle;

class UnlockConsoleEvent : public Event {
    public:
        bool processEvent(print_f print, Game *);
        bool isUnlockConsoleEvent() { return true; }
};

#endif
