#include "UnlockConsoleEvent.h"
#include "Game.h"

bool UnlockConsoleEvent::processEvent(print_f print, Game *game) {

    game->state = WAIT_PUZZLE;
    game->dirty = true;
    game->justUnlocked = true;

    // There is only one unlock event, we just re-use it.
    return false;
}
