#include <gtest/gtest.h>

#include <jbi/interpreter/arithmetic_operation.h>

class arithmetic_operation_tests : public ::testing::Test
{
protected:
    jbi::arithmetic_operation addition = jbi::arithmetic_operation::addition();
    jbi::arithmetic_operation subtraction = jbi::arithmetic_operation::subtraction();
    jbi::arithmetic_operation multiplication = jbi::arithmetic_operation::multiplication();
    jbi::arithmetic_operation division = jbi::arithmetic_operation::division();
    jbi::arithmetic_operation exponentiation = jbi::arithmetic_operation::exponentiation();
};

TEST_F(arithmetic_operation_tests, apply_test)
{
    EXPECT_EQ(10, addition.apply(7, 3));
    EXPECT_DOUBLE_EQ(4.76, addition.apply(3.14, 1.62));
    EXPECT_DOUBLE_EQ(8.62, addition.apply(7, 1.62));

    EXPECT_EQ(4, subtraction.apply(7, 3));
    EXPECT_DOUBLE_EQ(1.52, subtraction.apply(3.14, 1.62));
    EXPECT_DOUBLE_EQ(5.38, subtraction.apply(7, 1.62));

    EXPECT_EQ(21, multiplication.apply(7, 3));
    EXPECT_DOUBLE_EQ(1.57, multiplication.apply(3.14, 0.5));
    EXPECT_DOUBLE_EQ(10.5, multiplication.apply(7, 1.5));

    EXPECT_EQ(3, division.apply(7, 2));
    EXPECT_DOUBLE_EQ(3.0, division.apply(7.5, 2.5));
    EXPECT_DOUBLE_EQ(3.5, division.apply(7.0, 2));

    EXPECT_EQ(49, exponentiation.apply(7, 2));
    EXPECT_DOUBLE_EQ(2.25, exponentiation.apply(1.5, 2.0));
    EXPECT_DOUBLE_EQ(8.0, exponentiation.apply(64, 0.5));
}

TEST_F(arithmetic_operation_tests, division_by_zero_test)
{
    EXPECT_THROW(division.apply(1, 0), jbi::arithmetic_exception);
    EXPECT_NO_THROW(division.apply(1.0, 0));
    EXPECT_NO_THROW(division.apply(1, 0.0));
}

TEST_F(arithmetic_operation_tests, equality_operators_test)
{
    EXPECT_TRUE(addition == addition);
    EXPECT_FALSE(addition != addition);

    EXPECT_TRUE(addition != subtraction);
    EXPECT_FALSE(addition == subtraction);

    EXPECT_TRUE(addition != multiplication);
    EXPECT_FALSE(addition == multiplication);

    EXPECT_TRUE(addition != division);
    EXPECT_FALSE(addition == division);

    EXPECT_TRUE(addition != exponentiation);
    EXPECT_FALSE(addition == exponentiation);
}

TEST_F(arithmetic_operation_tests, from_symbol_test)
{
    EXPECT_EQ(addition, jbi::arithmetic_operation::from_symbol('+'));
    EXPECT_EQ(subtraction, jbi::arithmetic_operation::from_symbol('-'));
    EXPECT_EQ(multiplication, jbi::arithmetic_operation::from_symbol('*'));
    EXPECT_EQ(division, jbi::arithmetic_operation::from_symbol('/'));
    EXPECT_EQ(exponentiation, jbi::arithmetic_operation::from_symbol('^'));

    EXPECT_THROW(jbi::arithmetic_operation::from_symbol('%'), jbi::argument_exception);
}
