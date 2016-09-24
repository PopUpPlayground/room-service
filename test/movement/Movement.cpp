#include "Map.h"
#include "unity.h"
#include <string.h>
#include "DoorPortal.h"
#include "Actor.h"

#ifdef UNIT_TEST

void consolePrint(const char *string) {
    printf("%s",string);
}

// This tests a simple three-room map. The rooms are connected in a line.
void test_Movement() {
    Map map;
    Actor *cannibal;

    map.newRoom("Foyer",1,1);
    map.newRoom("Lounge",2,1);
    map.newRoom("Bathroom",3,1);

    map.newBiDoor(1,2);
    map.newBiDoor(2,3);

    TEST_ASSERT_EQUAL_STRING(map.map[1]->name,"Foyer");

    // TODO: Test other properties.

    // NB: Starts in room 1.
    cannibal = new Actor( "Shia LaBeouf", 100, 1, 9001, NULL, NULL );

    TEST_ASSERT_EQUAL(1, cannibal->room);

    // MOVE THE CANNIBAL.
    map.map[1]->exits[2]->trigger(
        consolePrint,
        cannibal,
        map.map[2]
    );

    TEST_ASSERT_EQUAL(2, cannibal->room);

    delete cannibal;
}



int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_Movement);

    UNITY_END();

    return 0;
}

#endif
