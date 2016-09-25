#ifndef LOCKEVENT_H
#define LOCKEVENT_H

#include "Event.h"
#include "types.h"

class LockEvent : public Event {
    private:
        const code_t code;
        const puzzle_t puzzle;
    public:
        LockEvent(const code_t _code, const puzzle_t _puzzle) :code(_code), puzzle(_puzzle)  { };
        void processEvent(print_f print, Game *);
};

#endif
