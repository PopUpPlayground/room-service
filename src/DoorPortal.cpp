#include "DoorPortal.h"
#include "Room.h"

// TODO: Moves an actor, or causes them to recalculate their
// route if the door is locked.
void DoorPortal::trigger(print_f print, Actor *actor, const Room *dst) {

    // TODO: Take locks into account. We probably want to pass a GameState
    // object that makes them accessible.
    
    // When a door is triggered, we move the actor! :D
    actor->room = dst->number;

    print(actor->name);
    print(" moves to ");
    print(dst->name);
    print("\n");
}
