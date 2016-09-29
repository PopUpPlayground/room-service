#include "MoveEvent.h"
#include "GoalEvent.h"
#include "Game.h"
#include "types.h"
#include "Actor.h"

// TODO: This is a big, ugly function, and I think a lot
// of it probably shold be on Actor, rather than here.

bool MoveEvent::processEvent(print_f print, Game *game) {

    // It's lazy setting this here, since they might not move, but it's
    // sure easy. :)
    game->dirty = true;

    // print("Move event triggered for ");
    // print(actor->name);
    // print(": ");

    // const Room *currentRoom = game->map.map[actor->room];

    // print(currentRoom->name);
    
    // Pop the first element off the route.
    room_t next = *(actor->path.begin());
    actor->path.erase( actor->path.begin() );

    // Debug: Show path.
    // actor->showPath(print);

    Portal *door = game->map.map[actor->room]->exits[next];
    Room *room = game->map.map[next];

    if (room == NULL) {
        print("...THEY FALL THROUGH A SPACE-TIME RIFT TO A VOID ROOM\n");
        return false;
    }

    // print(" -> ");
    // print(room->name);

    if (door == NULL) {
        print("...BUT THE DOOR, LIKE THE CAKE, IS A LIE!\n");
        return false;
    }
    
    // The door trigger schedules the next move, a wait, or
    // reconsideration of life choices. I think we could have
    // better architecture here.
    door->trigger(print, actor, room, game);

    // MoveEvents are always statically assigned
    return false;
}
