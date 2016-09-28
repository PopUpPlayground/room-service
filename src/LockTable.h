#ifndef LOCKTABLE_H
#define LOCKTABLE_H

#include <map>
#include <string>
#include "types.h"

class Puzzle;

// A global table of locks. Since not many locks are active at once, it's
// easier to have them all in one place, rather than setting them on
// the individual portals.

// The locktable is just the identifier (room, door, floor, etc)
// and the code that was used to lock it.
typedef std::multimap<std::string, Puzzle *> locks_t;

class LockTable {
    private:

    public:
        // Probably better private
        locks_t locks;

        void addLock(const code_t code, Puzzle *puzzle);
        void rmLock(const code_t code, Puzzle *puzzle);
        bool checkLock(const char *code);
};

#endif
