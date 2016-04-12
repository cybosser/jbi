#include <gtest/gtest.h>

#include <jbi/algorithm/pp.h>

TEST(algorithm_pp_tests, index_of_test)
{
    EXPECT_EQ(0, (jbi::pp::index_of<char, char, short, int>::value));
    EXPECT_EQ(1, (jbi::pp::index_of<short, char, short, int>::value));
    EXPECT_EQ(2, (jbi::pp::index_of<int, char, short, int>::value));
    EXPECT_EQ(jbi::pp::npos, (jbi::pp::index_of<long, char, short, int>::value));
}

TEST(algorithm_pp_tests, front_test)
{
    EXPECT_TRUE((std::is_same<char, jbi::pp::front<char, short, int>>::value));
    EXPECT_TRUE((std::is_same<int, jbi::pp::front<int, short, char>>::value));
}

TEST(algorithm_pp_tests, back_test)
{
    EXPECT_TRUE((std::is_same<int, jbi::pp::back<char, short, int>>::value));
    EXPECT_TRUE((std::is_same<char, jbi::pp::back<int, short, char>>::value));
}
