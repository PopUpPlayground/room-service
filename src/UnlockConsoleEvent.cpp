#include "UnlockConsoleEvent.h"
#include "Game.h"

void UnlockConsoleEvent::processEvent(print_f print, Game *game) {
    game->state = WAIT_PUZZLE;
    game->dirty = true;
}
