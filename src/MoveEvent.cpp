#include "MoveEvent.h"
#include "GoalEvent.h"
#include "Game.h"
#include "types.h"
#include "Actor.h"

// TODO: This is a big, ugly function, and I think a lot
// of it probably shold be on Actor, rather than here.

void MoveEvent::processEvent(print_f print, Game *game) {

    print("Move event triggered for ");
    print(actor->name);
    print(" in room: ");

    const Room *currentRoom = game->map.map[actor->room];

    print(currentRoom->name);
    print("\n");
    
    // Pop the first element off the route.
    room_t next = *(actor->path->begin());
    actor->path->erase( actor->path->begin() );

    // Debug: Show path.
    actor->showPath(print);

    Portal *door = game->map.map[actor->room]->exits[next];
    Room *room = game->map.map[next];

    if (room == NULL) {
        print("...THEY FALL THROUGH A SPACE-TIME RIFT TO A VOID ROOM\n");
        return;
    }

    print("...Trying the door to ");
    print(room->name);
    print("\n");

    if (door == NULL) {
        print("...BUT THE DOOR, LIKE THE CAKE, IS A LIE!\n");
        return;
    }
    
    door->trigger(print, actor, room);
    print("...The door was no match for ");
    print(actor->name);
    print("!!\n");

    // Trigger NEXT movement event!
    if (room->number == actor->destination->room) {
        print(actor->name);
        print(" has arrived at their final destination!\n");

        // Schedule next goal.
        // TODO: Use sigmas
        game->scheduleOffsetEvent( actor->destination->wait, new GoalEvent(actor) );
    }
    else {
        // Schedule next move.
        game->scheduleOffsetEvent( actor->speed, new MoveEvent(actor) );
    }
}
