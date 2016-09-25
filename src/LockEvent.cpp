#include "LockEvent.h"
#include "Game.h"

// This should probably *release* the lock after a point, too!
void LockEvent::processEvent(print_f print, Game *game) {
    game->map.lockDoor(code, puzzle);
}
