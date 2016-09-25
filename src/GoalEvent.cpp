#include "GoalEvent.h"
#include "Game.h"
#include "Actor.h"
#include <string>

std::string GoalEvent::processEvent(Game *queue) {
    return actor->recomputeGoal(map);
}
