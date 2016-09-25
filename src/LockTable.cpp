#include "LockTable.h"
#include <string>

void LockTable::addLock(const code_t code, const puzzle_t puzzle) {
    locks.insert(std::make_pair(std::string (code), std::string (puzzle)));
}

bool LockTable::checkLock(const char *code) {
    std::string strCode (code);
    return locks.count(strCode) > 0;
}
