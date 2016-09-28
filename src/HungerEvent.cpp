#include "HungerEvent.h"
#include "Game.h"
#include <stdio.h>

bool HungerEvent::processEvent(print_f print, Game *game) {
    game->globalHunger++;

    char buf[10];
    snprintf(buf,10,"%d\n",game->globalHunger);

    print("Global hunger is now: ");
    print(buf);

    // Schedule our next tick.
    game->scheduleOffsetEvent(tickLength, this);

    // Reusing event object
    return false;
}
