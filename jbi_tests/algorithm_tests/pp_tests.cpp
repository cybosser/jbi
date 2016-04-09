#include <gtest/gtest.h>

#include <jbi/algorithm/pp.h>

TEST(algorithm_pp_tests, index_of_test)
{
    EXPECT_EQ(0, (jbi::pp::index_of<char, char, short, int>::value));
    EXPECT_EQ(1, (jbi::pp::index_of<short, char, short, int>::value));
    EXPECT_EQ(2, (jbi::pp::index_of<int, char, short, int>::value));
    EXPECT_EQ(jbi::pp::noindex, (jbi::pp::index_of<long, char, short, int>::value));
}
