#include "PlayerHaxxedEvent.h"
#include "Game.h"

// Check if the haxx room is occupied, and fire if so.
// XXX: Race condition; if the console is already locked, it'll unlock early for the players.
bool PlayerHaxxedEvent::processEvent(print_f print, Game *game) {

    print("Testing haxx\n");

    // Have we cooled down enough since the last hack?
    if (lastHaxx + coolDown < game->time) {
        print("Haxx window opened\n");
        maybeHaxx(print, game);
    }

    // Schedule our next tick
    print("Scheduling next haxx check\n");
    game->scheduleOffsetEvent(checkFreq,this);

    return false; // Don't clear event memory.
}

void PlayerHaxxedEvent::maybeHaxx(print_f print, Game *game) {
    // Walk through all our actors, and trigger if any are in our room.
    for (actors_t::iterator actor_it = game->actors.begin(); actor_it != game->actors.end(); ++actor_it) {
        if ((*actor_it)->room == room) {
            
            print("H4xX0r in position\n");

            // Aww yis, prepared to be h4xX0r3d
            
            const char *roomName = game->map.map[room]->name;
            
            game->lockConsole("Override from", roomName, haxxLength);
            lastHaxx = game->time;

            print("Pl4y3rZ h4Xx0r3d from ");
            print(roomName);
            print("!!!\n");

            // Clear all the door locks.
            print("Clearing locks\n");
            game->events.clearLocks(print, game);

            print("Yielding\n");

            return;
        }
    }
    print("No H4xX0rs in position");
}
