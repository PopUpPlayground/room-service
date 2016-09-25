#include "EventQueue.h"

void EventQueue::runEvents(print_f stream, millis_t time, Game *game) {

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
        (*stream)( i->second->processEvent(game).c_str() );

        // The event has fired! Now we deconstruct it.
        delete i->second;

        // And now let's delete the element in the multimap itself. This would
        // be easy if we were using C++11, but apparently gcc doesn't support
        // that, so I'm going to cry into this code instead. (Thanks,
        // Stackoverflow....)

        events_t::iterator save = i;
        ++save;
        events.erase(i);
        i = save;
    }
}

// Schedules an event for the future (or the past, which will fire
// next time runEvents is called).
void EventQueue::scheduleEvent(millis_t time, Event *event) {
    events.insert( std::make_pair( time, event) );
}
