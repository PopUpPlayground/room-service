#ifndef LOCKTABLE_H
#define LOCKTABLE_H

#include <map>

// A global table of locks. Since not many locks are active at once, it's
// easier to have them all in one place, rather than setting them on
// the individual portals.

class lockTable {
    public:

        // The locktable is just the identifier (room, door, floor, etc)
        // and the code that was used to lock it.
        std::multimap<ident_t, code_t> locks;
};

#endif
