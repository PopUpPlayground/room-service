#include "HungerEvent.h"
#include "Game.h"

void HungerEvent::processEvent(print_f print, Game *game) {
    print("Hunger++\n");
    game->globalHunger++;

    // Schedule our next tick.
    game->scheduleOffsetEvent(tickLength, new HungerEvent(tickLength));
}
