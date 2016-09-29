#ifndef PLAYERHAXXED_H
#define PLAYERHAXXED_H

#include "types.h"
#include "Event.h"

class Game;

class PlayerHaxxedEvent : public Event {
    private:
        const millis_t checkFreq;   // How often do we check?
        const millis_t coolDown;    // Minimum time between haxx
        const millis_t haxxLength;  // How long are they haxxed for?
        const room_t   room;        // Which room gets checked for h4xX0rz?
              millis_t lastHaxx;    // When were we last haxxed?

        void maybeHaxx(print_f print, Game *game);

    public:
        bool processEvent(print_f, Game *);
        
        PlayerHaxxedEvent(
            const millis_t freq, const millis_t cool, const millis_t length, const room_t _room
        ) :checkFreq(freq), coolDown(cool), haxxLength(length), room(_room), lastHaxx(0) { }
};

#endif
