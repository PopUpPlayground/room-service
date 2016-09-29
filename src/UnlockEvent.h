#ifndef UNLOCKEVENT_H
#define UNLOCKEVENT_H

#include "Event.h"
#include "types.h"

class Puzzle;

class UnlockEvent : public Event {
    private:
        const code_t code;
        Puzzle *puzzle;

    public:
        UnlockEvent(const code_t _code, Puzzle *_puzzle) :code(_code), puzzle(_puzzle) { };
        bool processEvent(print_f print, Game *);
        bool isUnlockEvent() { return true; }
};

#endif
