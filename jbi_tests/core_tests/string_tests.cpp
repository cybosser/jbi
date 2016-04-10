#include <gtest/gtest.h>

#include <jbi/core/string.h>

TEST(core_string_tests, to_string_test)
{
    EXPECT_EQ("Lorem Ipsum", jbi::to_string("Lorem Ipsum"));
    EXPECT_EQ("1984", jbi::to_string(1984));
    EXPECT_EQ("3.14", jbi::to_string(3.14));
    EXPECT_EQ("z", jbi::to_string('z'));
}
