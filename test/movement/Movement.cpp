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
    map_t map;
    DoorPortal door;
    Actor *cannibal;

    map[1] = new Room("Foyer", 1);
    map[1]->exits[2] = door;

    map[2] = new Room("Lounge", 2);
    map[2]->exits[1] = door;
    map[2]->exits[3] = door;

    map[3] = new Room("Bathroom", 3);
    map[3]->exits[2] = door;

    TEST_ASSERT_EQUAL_STRING(map[1]->name,"Foyer");

    // TODO: Test other properties.

    // NB: Starts in room 1.
    cannibal = new Actor( "Shia LaBeouf", 100, 1, 9001, NULL, NULL );

    TEST_ASSERT_EQUAL(1, cannibal->room);

    // MOVE THE CANNIBAL.
    door.trigger(
        consolePrint,
        cannibal,
        map[2]
    );

    TEST_ASSERT_EQUAL(2, cannibal->room);

    // This frees up all the memory we allocated and makes
    // valgrind happy. We should probably make a proper map class
    // and give it a custom destructor.
    for (map_t::iterator it=map.begin(); it!=map.end();) {
        map_t::iterator old = it;
        ++it;

        delete old->second;
        map.erase(old);
    }

    delete cannibal;
}



int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_Movement);

    UNITY_END();

    return 0;
}

#endif
