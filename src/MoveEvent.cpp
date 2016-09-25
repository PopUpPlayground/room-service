#include "MoveEvent.h"
#include "Game.h"
#include <string>
#include "types.h"
#include "Actor.h"

std::string MoveEvent::processEvent(Game *game) {
    
    // Pop the first element off the route.
    room_t next = *(actor->path->begin());
    actor->path->erase( actor->path->begin() );

    Portal *door = game->map.map[actor->room]->exits[next];
    Room *room = game->map.map[next];
        
    door->trigger(NULL, actor, room);

    return "STUB!!";
}
