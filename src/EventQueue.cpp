#include "EventQueue.h"

void EventQueue::runEvents(print_f stream, millis_t time) {

    // Walk through all our events, but only until we reach the end, or we reach an
    // event where we haven't reached the time for it to trigger yet, *erasing* as
    // we go!
    for (
        events_t::iterator i = events.begin();
        i != events.end() && i->first <= time;
        // Increment happens in the main loop.
    ) {
        // Process the event, and send its output to the stream (which goes
        // to the game runner, or our test framework)
        (*stream)( i->second.processEvent().c_str() );


        // And now let's delete the element. This would be easy if we were
        // using C++11, but apparently gcc doesn't support that, so I'm going
        // to cry into this code instead. (Thanks, Stackoverflow....)

        events_t::iterator save = i;
        ++save;
        events.erase(i);
        i = save;
    }
}
