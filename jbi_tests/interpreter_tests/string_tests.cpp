#include <gtest/gtest.h>

#include <jbi/interpreter/string.h>

TEST(from_string_tests, numbers_test)
{
    EXPECT_EQ(1948, jbi::from_string<int>("1948"));
    EXPECT_EQ(-1948, jbi::from_string<int>("-1948"));

    EXPECT_DOUBLE_EQ(-3.14, jbi::from_string<double>("-3.14"));
    EXPECT_DOUBLE_EQ(3.14, jbi::from_string<double>("3.14"));
}

TEST(from_string_tests, non_numbers_test)
{
    EXPECT_THROW(jbi::from_string<double>("foo"), jbi::value_exception);
    EXPECT_THROW(jbi::from_string<int>("bar"), jbi::value_exception);
}

TEST(from_string_tests, overflow_test)
{
    EXPECT_THROW(jbi::from_string<int>(std::to_string(std::numeric_limits<unsigned int>::max())), jbi::value_exception);
}
