#include "UnlockEvent.h"
#include "Game.h"

void UnlockEvent::processEvent(print_f print, Game *game) {

    // Force map refresh.
    game->dirty = true;

    print("Expiring lock on ");
    print(code.c_str());
    print(" using puzzle code ");
    print(puzzle.c_str());
    print("\n");

    game->map.unlockDoor(code, puzzle);
}
