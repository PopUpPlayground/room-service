#include "MsgEvent.h"
#include "EventQueue.h"
#include "Game.h"
#include "unity.h"
#include <string.h>

#ifdef UNIT_TEST

void test_MsgEvent() {
    const char *foo = "foo";

    MsgEvent e (foo);
    Game game;

    TEST_ASSERT_EQUAL_STRING( "foo", e.processEvent(&game).c_str() );
    TEST_ASSERT( strcmp( "bar", e.processEvent(&game).c_str() ) );
}

// This would be better done with a closure and a variable we can
// test.
void helper_never_call_me(const char *) {
    TEST_FAIL_MESSAGE("Never to be called function called");
}

void helper_pass_string(const char *input) {
    TEST_ASSERT_EQUAL_STRING("pass", input);
}

void test_EventQueue_empty() {
    EventQueue events;
    Game game;

    // No events on the queue, so this should do nothing.
    events.runEvents(helper_never_call_me, 9001, &game);
}

void test_EventQueue_single() {
    EventQueue events;
    Game game;

    events.scheduleEvent(9000, new MsgEvent("pass") );

    // Should not fire.
    events.runEvents(helper_never_call_me,8999, &game);

    // Should fire
    events.runEvents(helper_pass_string,9000, &game);

    // TODO: Test events queue is now empty.
}

int main(int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_MsgEvent);
    RUN_TEST(test_EventQueue_empty);
    RUN_TEST(test_EventQueue_single);

    UNITY_END();

    return 0;
}

#endif
