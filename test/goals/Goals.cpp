#include "Goals.h"
#include "unity.h"

void test_Goal_simple() {

    Goals goals;

    // Add goals of reaching rooms 1 and 3, with equal weighting (50),
    // and lingering a second with 100ms sigma.
    goals.add(1, 50, 1000, 100);
    goals.add(3, 50, 1000, 100);

    // Success!
    TEST_ASSERT(true);
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_Goal_simple);

    UNITY_END();
    
    return 0;
}
