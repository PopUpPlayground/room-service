#include <gtest/gtest.h>

class MyTest : public ::testing::Test { };

TEST_F(MyTest, SimpleTest) {
    const char *foo = "foo";

    EXPECT_EQ(foo, "foo");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
