#include "DoorPortal.h"
#include "Room.h"
#include <string.h>
#include "Debug.h"
#include "Game.h"
#include "Actor.h"
#include "GoalEvent.h"
#include "MoveEvent.h"

// Moves an actor, or causes them to recalculate their
void DoorPortal::trigger(print_f print, Actor *actor, const Room *dst, Game *game) {

    assert(dst != NULL);
    assert(game != NULL);

    if (game->map.isLocked(actor->room, dst)) {
        print("(LOCKED!!)\n");

        // print("...but the door is locked! ");
        // print(actor->name);
        // print(" reconsiders their life choices.\n");

        // Zero delay here means we'll kick off next tick.
        game->scheduleOffsetEvent(0, &(actor->goalEvent));
    }
    else {
        // Not locked, let's go!
        moveActor(print, actor, dst);

        // print("...The door was no match for ");
        // print(actor->name);
        // print("!!\n");

        if (actor->destination == NULL) {
            print(actor->name);
            print(" has no fixed destination! This is **A BUG** unless we're unit testing.\n");
        }
        else if (actor->destination->room == dst->number) {
            // print(actor->name);
            // print(" has arrived at their final destination!\n");
            
            print(" (now resting)\n");

            // Schedule next goal.
            // TODO: Use sigmas
            game->scheduleOffsetEvent( actor->destination->wait, &(actor->goalEvent));
        }
        else {
            // Schedule next move.
            // print(actor->name);
            // print(" is in transit, scheduling next move.\n");

            print("\n");    // No extra info to provide.

            game->scheduleOffsetEvent( actor->speed, &(actor->moveEvent) );
        }
    }
}

// Doors are lockable if they have a code.
bool DoorPortal::isLockable() {
    return code != NULL;
}

bool DoorPortal::isLocked(LockTable *table) {

    Debug("Testing door lock\n");

    if (! isLockable() ) {
        return false;
    }

    return table->checkLock(code);
}
