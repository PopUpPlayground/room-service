#ifndef GAME_H
#define GAME_H

#include "EventQueue.h"
#include "Map.h"
#include <vector>

// This is a top level game class. It's a composite of everything one needs to run the game,
// but with no hardware dependence so we can test it in the cloud.

class Game {
    public:
        EventQueue events;
        Map map;
        std::vector<Actor *> actors;
};

#endif
