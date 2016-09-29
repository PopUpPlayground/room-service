#include "Goals.h"
#include "unity.h"

void test_Goal_simple() {

    Map map;
    map.newRoom("Meh",1,"1");
    map.newRoom("Moop",2,"1");
    map.newRoom("Mork",3,"1");

    Goals goals(&map);

    // Add goals of reaching rooms 1 and 3, with equal weighting (50),
    // and lingering a second with 100ms sigma.
    goals.add(1, 50, 1000, 100);
    goals.add(3, 50, 1000, 100);

    // With our simple table, we should always pick the room we're *not* in
    // as our goal.
    TEST_ASSERT_EQUAL(3, goals.findGoal(1)->room);
    TEST_ASSERT_EQUAL(1, goals.findGoal(3)->room);

    // Now add an extra room
    goals.add(2, 50, 1000, 100);

    // Walk through each room, picking a new destination for each,
    // making sure it's not the current room. Do this 100 times, so
    // if there's a weird edge case, we might find it.
    for (int tests = 100; tests >= 0; tests--) {
        for (int i=1; i <= 3; i++) {
            TEST_ASSERT(i != goals.findGoal(i)->room);
        }
    }

}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_Goal_simple);

    UNITY_END();
    
    return 0;
}
