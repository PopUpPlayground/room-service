#ifdef NATIVE

#include "RoomService.h"
#include "Game.h"
#include <unistd.h>
#include <iostream>

typedef RoomService game_t;

game_t game;

void consolePrint(const char *string) {
    std::cerr << string;
}

int main(int argc, char **argv) {
    millis_t millis = 1;

    game.start(consolePrint, millis);

    while(millis < 31 * 60 * 1000) {
        usleep(1);
        millis += 100;
        game.tick(consolePrint, millis);
    }

    consolePrint("\nGame Ended\n");

    return 0;
}

#endif
