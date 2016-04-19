#include <gtest/gtest.h>

#include <jbi/interpreter/arithmetic_operation.h>

TEST(interpreter_arithmetic_operation_tests, equality_operators_test)
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

TEST(interpreter_arithmetic_operation_tests, from_symbol_test)
{
    EXPECT_EQ(jbi::arithmetic_operation::addition(), jbi::arithmetic_operation::from_symbol('+'));
    EXPECT_EQ(jbi::arithmetic_operation::subtraction(), jbi::arithmetic_operation::from_symbol('-'));
    EXPECT_EQ(jbi::arithmetic_operation::multiplication(), jbi::arithmetic_operation::from_symbol('*'));
    EXPECT_EQ(jbi::arithmetic_operation::division(), jbi::arithmetic_operation::from_symbol('/'));
    EXPECT_EQ(jbi::arithmetic_operation::exponentiation(), jbi::arithmetic_operation::from_symbol('^'));

    EXPECT_THROW(jbi::arithmetic_operation::from_symbol('%'), jbi::argument_exception);
}
