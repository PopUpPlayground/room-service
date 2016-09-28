#ifndef UNLOCKEVENT_H
#define UNLOCKEVENT_H

#include "Event.h"
#include "types.h"

class UnlockEvent : public Event {
    private:
        const code_t code;
        const puzzle_t puzzle;

    public:
        UnlockEvent(const code_t _code, const puzzle_t _puzzle) :code(_code), puzzle(_puzzle) { };
        void processEvent(print_f print, Game *);
};

#endif
