#include <gtest/gtest.h>

#include <jbi/interpreter/symbol_table.h>

TEST(symbol_table_tests, get_test)
{
    jbi::symbol_table symbols;

    EXPECT_THROW(symbols.get("foo"), jbi::argument_exception);

    symbols.set("foo", 3.14);

    EXPECT_EQ(3.14, jbi::get<double>(symbols.get("foo")));
}

TEST(symbol_table_tests, override_test)
{
    jbi::symbol_table symbols;

    symbols.set("foo", 3.14);
    EXPECT_EQ(3.14, jbi::get<double>(symbols.get("foo")));

    symbols.set("foo", 1948);
    EXPECT_EQ(1948, jbi::get<int>(symbols.get("foo")));
}

TEST(symbol_table_tests, contains_test)
{
    jbi::symbol_table symbols;

    EXPECT_FALSE(symbols.contains("foo"));

    symbols.set("foo", 3.14);

    EXPECT_TRUE(symbols.contains("foo"));
}
