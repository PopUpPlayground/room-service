#include "Portal.h"
#include "Actor.h"
#include "Room.h"

// Moes the actor to the given room, without checking for locks or anything
void Portal::moveActor(print_f print, Actor *actor, const Room *dst) {
    actor->room = dst->number;

    print(actor->name);
    print(" moves to ");
    print(dst->name);
    print("\n");

}
