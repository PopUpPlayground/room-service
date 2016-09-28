#ifndef HUNGEREVENT_H
#define HUNGEREVENT_H

#include "Event.h"

class HungerEvent : public Event {
    private:
        const millis_t tickLength;      // How often to increase hunger?
    public:
        void processEvent(print_f, Game *);

        // Default tick length is one minute.
        HungerEvent(millis_t _tickLength = 60 * 1000) :tickLength(_tickLength) { }
};

#endif
