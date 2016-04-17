#include <gtest/gtest.h>

#include <jbi/interpreter/type.h>

TEST(type_tests, test_equality_operators)
{
    EXPECT_EQ(jbi::type::int_(), jbi::type::int_());
    EXPECT_EQ(jbi::type::double_(), jbi::type::double_());

    EXPECT_NE(jbi::type::int_(), jbi::type::double_());
}

TEST(type_tests, common_type)
{
    EXPECT_EQ(jbi::type::int_(), jbi::type::common_type(jbi::type::int_(), jbi::type::int_()));
    EXPECT_EQ(jbi::type::double_(), jbi::type::common_type(jbi::type::double_(), jbi::type::double_()));

    EXPECT_EQ(jbi::type::double_(), jbi::type::common_type(jbi::type::double_(), jbi::type::int_()));
    EXPECT_EQ(jbi::type::double_(), jbi::type::common_type(jbi::type::int_(), jbi::type::double_()));
}
