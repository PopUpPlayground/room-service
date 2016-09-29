#include "Map.h"
#include "unity.h"
#include <string.h>
#include "DoorPortal.h"

#ifdef UNIT_TEST

// This tests a simple three-room map. The rooms are connected in a line.
void test_Map() {
    Map map;

    map.newRoom("Start", 1, "1");
    map.newRoom("Middle", 2, "1");
    map.newRoom("End", 3, "1");

    map.newBiDoor(1,2);
    map.newBiDoor(2,3);

    TEST_ASSERT_EQUAL_STRING(map.map[1]->name,"Start");

    // TODO: Test other properties.
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_Map);

    UNITY_END();

    return 0;
}

#endif
