#include "UnlockEvent.h"
#include "Game.h"

bool UnlockEvent::processEvent(print_f print, Game *game) {

    // Force map refresh.
    game->dirty = true;

    print("Expiring lock on ");
    print(code.c_str());
    print("\n");

    game->map.unlockDoor(code, puzzle);

    // Unlocks are dynamically allocted, so make sure
    // we free our memory
    return true;
}
