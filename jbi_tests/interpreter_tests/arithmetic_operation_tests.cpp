#include <gtest/gtest.h>

#include <jbi/interpreter/arithmetic_operation.h>

TEST(arithmetic_operation_tests, apply_test)
{
    jbi::arithmetic_operation add = jbi::arithmetic_operation::addition();

    EXPECT_EQ(10, add.apply(7, 3));
    EXPECT_DOUBLE_EQ(4.76, add.apply(3.14, 1.62));
    EXPECT_DOUBLE_EQ(8.62, add.apply(7, 1.62));

    jbi::arithmetic_operation subtract = jbi::arithmetic_operation::subtraction();

    EXPECT_EQ(4, subtract.apply(7, 3));
    EXPECT_DOUBLE_EQ(1.52, subtract.apply(3.14, 1.62));
    EXPECT_DOUBLE_EQ(5.38, subtract.apply(7, 1.62));

    jbi::arithmetic_operation multiply = jbi::arithmetic_operation::multiplication();

    EXPECT_EQ(21, multiply.apply(7, 3));
    EXPECT_DOUBLE_EQ(1.57, multiply.apply(3.14, 0.5));
    EXPECT_DOUBLE_EQ(10.5, multiply.apply(7, 1.5));

    jbi::arithmetic_operation divide = jbi::arithmetic_operation::division();

    EXPECT_EQ(3, divide.apply(7, 2));
    EXPECT_DOUBLE_EQ(3.0, divide.apply(7.5, 2.5));
    EXPECT_DOUBLE_EQ(3.5, divide.apply(7.0, 2));

    jbi::arithmetic_operation exponentiate = jbi::arithmetic_operation::exponentiation();

    EXPECT_EQ(49, exponentiate.apply(7, 2));
    EXPECT_DOUBLE_EQ(2.25, exponentiate.apply(1.5, 2.0));
    EXPECT_DOUBLE_EQ(8.0, exponentiate.apply(64, 0.5));
}

TEST(arithmetic_operation_tests, equality_operators_test)
{
    EXPECT_TRUE(jbi::arithmetic_operation::addition() == jbi::arithmetic_operation::addition());
    EXPECT_FALSE(jbi::arithmetic_operation::addition() != jbi::arithmetic_operation::addition());

    EXPECT_TRUE(jbi::arithmetic_operation::addition() != jbi::arithmetic_operation::subtraction());
    EXPECT_FALSE(jbi::arithmetic_operation::addition() == jbi::arithmetic_operation::subtraction());

    EXPECT_TRUE(jbi::arithmetic_operation::addition() != jbi::arithmetic_operation::multiplication());
    EXPECT_FALSE(jbi::arithmetic_operation::addition() == jbi::arithmetic_operation::multiplication());

    EXPECT_TRUE(jbi::arithmetic_operation::addition() != jbi::arithmetic_operation::division());
    EXPECT_FALSE(jbi::arithmetic_operation::addition() == jbi::arithmetic_operation::division());

    EXPECT_TRUE(jbi::arithmetic_operation::addition() != jbi::arithmetic_operation::exponentiation());
    EXPECT_FALSE(jbi::arithmetic_operation::addition() == jbi::arithmetic_operation::exponentiation());
}

TEST(arithmetic_operation_tests, from_symbol_test)
{
    EXPECT_EQ(jbi::arithmetic_operation::addition(), jbi::arithmetic_operation::from_symbol('+'));
    EXPECT_EQ(jbi::arithmetic_operation::subtraction(), jbi::arithmetic_operation::from_symbol('-'));
    EXPECT_EQ(jbi::arithmetic_operation::multiplication(), jbi::arithmetic_operation::from_symbol('*'));
    EXPECT_EQ(jbi::arithmetic_operation::division(), jbi::arithmetic_operation::from_symbol('/'));
    EXPECT_EQ(jbi::arithmetic_operation::exponentiation(), jbi::arithmetic_operation::from_symbol('^'));

    EXPECT_THROW(jbi::arithmetic_operation::from_symbol('%'), jbi::argument_exception);
}
