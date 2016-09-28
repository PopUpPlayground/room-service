#include "Map.h"
#include "unity.h"
#include <string.h>
#include "DoorPortal.h"
#include "Actor.h"
#include "Game.h"
#include <stdio.h>
#include <iostream>

#ifdef UNIT_TEST

void consolePrint(const char *string) {
    fprintf(stderr,"%s",string);
}

// This tests a simple three-room map. The rooms are connected in a line.
void test_Movement() {
    Game game;
    Actor *cannibal;

    std::cerr << "First test...\n";

    game.map.newRoom("Foyer",1,1);
    game.map.newRoom("Lounge",2,1);
    game.map.newRoom("Bathroom",3,1);

    game.map.newBiDoor(1,2);
    game.map.newBiDoor(2,3);

    TEST_ASSERT_EQUAL_STRING(game.map.map[1]->name,"Foyer");

    // TODO: Test other properties.

    // NB: Starts in room 1.
    cannibal = new Actor( "Shia LaBeouf", 100, 1, 9001, NULL, NULL );

    TEST_ASSERT_EQUAL(1, cannibal->room);

    std::cerr << "Moving actor...\n";

    // MOVE THE CANNIBAL.
    game.map.map[1]->exits[2]->trigger(
        consolePrint,
        cannibal,
        game.map.map[2],
        &game
    );

    std::cerr << "Moved\n";

    TEST_ASSERT_EQUAL(2, cannibal->room);

    std::cerr << "First test complete\n";

    delete cannibal;
}

void test_MovementAdvanced() {
    Game game;

    game.map.newRoom("Foyer",1,1);
    game.map.newRoom("Lounge",2,1);
    game.map.newRoom("Bathroom",3,1);

    game.map.newBiDoor(1,2);
    game.map.newBiDoor(2,3);

    std::cerr << "Making Shia goals\n";

    Goals *shiaGoals = new Goals(&game.map);
    shiaGoals->add(3,10,2000,0);       // Foyer
    shiaGoals->add(1,10,2000,0);       // Bathroom

    Actor *cannibal = new Actor(
        "Shia LaBeouf",
        2000,               // Speed (move every 2000ms)
        1,                  // Starting room: Foyer
        50,                 // Hunger break
        shiaGoals,          // Regular goals
        shiaGoals           // Hungry goals
    );

    std::cerr << "Recomputing goals\n";

    Event *event = cannibal->recomputeGoal(consolePrint, &(game.map),0);

    std::cerr << "About to process move event.\n";
    event->processEvent(consolePrint,&game);
    std::cerr << "Move event processed.\n";

    TEST_ASSERT_EQUAL(2, cannibal->room);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_Movement);
    RUN_TEST(test_MovementAdvanced);

    UNITY_END();

    return 0;
}

#endif
