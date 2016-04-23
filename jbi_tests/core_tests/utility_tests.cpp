#include <gtest/gtest.h>

#include <jbi/core/utility.h>

TEST(utility_tests, is_one_of_test)
{
    EXPECT_TRUE(jbi::is_one_of('a', 'a', 'b', 'c'));
    EXPECT_TRUE(jbi::is_one_of('b', 'a', 'b', 'c'));
    EXPECT_TRUE(jbi::is_one_of('c', 'a', 'b', 'c'));
    EXPECT_FALSE(jbi::is_one_of('d', 'a', 'b', 'c'));
}