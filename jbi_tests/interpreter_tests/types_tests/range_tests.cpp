#include <gtest/gtest.h>

#include <jbi/interpreter/types/range.h>

TEST(range_tests, begin_end_test)
{
    jbi::range<int> range(0, 10);

    auto expected = range.start();
    for (auto it = std::begin(range); it != std::end(range); ++it, ++expected)
        EXPECT_EQ(expected, *it);

    EXPECT_EQ(expected, range.stop());
}

TEST(range_tests, invalid_range_test)
{
    EXPECT_THROW(jbi::range<int>(1, 0), jbi::argument_exception);
}

TEST(range_tests, empty_range_test)
{
    jbi::range<int> range(0, 0);

    auto begin = std::begin(range);
    auto end = std::end(range);

    EXPECT_EQ(begin, end);

    EXPECT_THROW(*begin, jbi::invalid_operation_exception);
    EXPECT_THROW(*end, jbi::invalid_operation_exception);
}
