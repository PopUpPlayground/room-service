#include "LockTable.h"
#include "Puzzle.h"
#include <string>

void LockTable::addLock(const code_t code, Puzzle *puzzle) {
    locks.insert(std::make_pair(std::string (code), puzzle));
}

// Wow C++, could you make this any more tricky?
// Surely there's a better way?

void LockTable::rmLock(const code_t code, Puzzle *puzzle) {
    std::pair<locks_t::iterator,locks_t::iterator> range = locks.equal_range(code);

    locks_t::iterator it = range.first;

    // code/puzzle pairs are assumed to be unique, and so we can break after the
    // first one.
    for (; it != range.second; ++it) {
        if (it->second == puzzle) {
            locks.erase(it);
            break;
        }
    }
}

bool LockTable::checkLock(const char *code) {
    std::string strCode (code);
    return locks.count(strCode) > 0;
}

