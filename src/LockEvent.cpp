#include "LockEvent.h"
#include "UnlockEvent.h"
#include "Game.h"

// TODO: Configurable times per lock.
const int lockTime = 10 * 1000; // 10 seconds

// This should probably *release* the lock after a point, too!
void LockEvent::processEvent(print_f print, Game *game) {

    // Force refresh of map state.
    game->dirty = true;

    print("Applying lock to ");
    print(code.c_str());
    print(" using puzzle code ");
    print(puzzle.c_str());
    print("\n");

    game->map.lockDoor(code, puzzle);

    // Schedule an unlock
    game->scheduleOffsetEvent(lockTime, new UnlockEvent(code, puzzle));
}
