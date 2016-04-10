#include <gtest/gtest.h>

#include <jbi/core/string.h>

TEST(core_string_tests, to_string_test)
{
    EXPECT_EQ(jbi::to_string("Lorem Ipsum"), "Lorem Ipsum");
    EXPECT_EQ(jbi::to_string(1984), "1984");
    EXPECT_EQ(jbi::to_string(3.14), "3.14");
    EXPECT_EQ(jbi::to_string('z'), "z");
}
