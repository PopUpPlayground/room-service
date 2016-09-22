#include "Map.h"
#include "unity.h"
#include <string.h>
#include "DoorPortal.h"

#ifdef UNIT_TEST

// This tests a simple three-room map. The rooms are connected in a line.
void test_Map() {
    map_t map;
    DoorPortal door;

    map[1] = new Room("Start");
    map[1]->exits[2] = door;

    map[2] = new Room("Middle");
    map[2]->exits[1] = door;
    map[2]->exits[3] = door;

    map[3] = new Room("End");
    map[3]->exits[2] = door;

    TEST_ASSERT_EQUAL_STRING(map[1]->name,"Start");

    // TODO: Test other properties.
    //
    // TODO: Do we need a map.clear here to tidy up memory?
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_Map);

    UNITY_END();

    return 0;
}

#endif
