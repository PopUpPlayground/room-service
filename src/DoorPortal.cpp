#include "DoorPortal.h"
#include "Room.h"

// TODO: Moves an actor, or causes them to recalculate their
// route if the door is locked.
void DoorPortal::trigger(print_f print, Actor *actor, const Room *dst) {

    // TODO: Take locks into account. We probably want to pass a GameState
    // object that makes them accessible.
    
    moveActor(print, actor, dst);
}
