#include "Actor.h"
#include "unity.h"
#include <string.h>

#ifdef UNIT_TEST

void test_Actor() {
    Actor *cannibal;

    cannibal = new Actor(
        "Shia LaBeouf",     // Name
        100,                // Speed
        404,                // Room
        9000               // Hunger Break
        // NULL,               // Regular Goals
        // NULL                // Hungry Goals
    );

    TEST_ASSERT_EQUAL_STRING("Shia LaBeouf", cannibal->name);

    delete cannibal;
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_Actor);

    UNITY_END();

    return 0;
}

#endif
