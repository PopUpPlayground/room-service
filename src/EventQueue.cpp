#include "EventQueue.h"
#include "UnlockEvent.h"

void EventQueue::runEvents(print_f print, millis_t time, Game *game) {

    // Walk through all our events, but only until we reach the end, or we reach an
    // event where we haven't reached the time for it to trigger yet, *erasing* as
    // we go!
    for (
        events_t::iterator i = events.begin();
        i != events.end() && i->first <= time;
        // Increment happens in the main loop.
    ) {
        i = fireEvent(print,game,i);
    }
}

// Schedules an event for the future (or the past, which will fire
// next time runEvents is called).
void EventQueue::scheduleEvent(millis_t time, Event *event) {
    events.insert( std::make_pair( time, event) );
}

// Fires all locks now.
void EventQueue::clearLocks(print_f print, Game *game) {
    for ( events_t::iterator i = events.begin(); i != events.end(); ) {

        if (i->second->isUnlockEvent()) {
            i = fireEvent(print, game, i);
        }
        else {
            ++i;
        }
    }
}

// Fires an event, returns iterator to next event
events_t::iterator EventQueue::fireEvent(print_f print, Game *game, events_t::iterator ev) {
    
    bool clearMem = ev->second->processEvent(print, game);

    // The event has fired! Now we deconstruct it if requested.
    if (clearMem) {
        delete ev->second;
    }

    // And now let's delete the element in the multimap itself. This would
    // be easy if we were using C++11, but apparently gcc doesn't support
    // that, so I'm going to cry into this code instead. (Thanks,
    // Stackoverflow....)

    events_t::iterator save = ev;
    ++save;
    events.erase(ev);
    return save;
}
