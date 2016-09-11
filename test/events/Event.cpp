#include "MsgEvent.h"
#include "unity.h"
#include <string.h>

#ifdef UNIT_TEST

void test_MsgEvent() {
    const char *foo = "foo";

    MsgEvent e (foo);

    TEST_ASSERT_EQUAL_STRING( "foo", e.processEvent().c_str() );
    TEST_ASSERT( strcmp( "bar", e.processEvent().c_str() ) );
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_MsgEvent);

    UNITY_END();

    return 0;
}

#endif
