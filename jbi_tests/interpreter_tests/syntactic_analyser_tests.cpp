#include <gtest/gtest.h>

#include <jbi/interpreter/syntactic_analyser.h>

std::string parse(const std::string& statement)
{
    // TODO mock lexical_analyser
    // TODO get rid of dependency on node::to_string method implementation
    jbi::syntactic_analyser parser{ jbi::lexical_analyser(statement) };
    return jbi::to_string(*parser.parse());
}

TEST(syntactic_analyser_tests, assignment_statement_test)
{
    EXPECT_EQ("id:foo = const:1", parse("var foo = 1"));

    EXPECT_THROW(parse("var * = 1"), jbi::syntax_exception);
    EXPECT_THROW(parse("var 1 = 1"), jbi::syntax_exception);
    EXPECT_THROW(parse("var out = 1"), jbi::syntax_exception);
}

TEST(syntactic_analyser_tests, associativity_test)
{
    EXPECT_EQ("id:foo = ((const:1 + const:2) - const:3)", parse("var foo = 1 + 2 - 3"));
    EXPECT_EQ("id:foo = ((const:1 - const:2) + const:3)", parse("var foo = 1 - 2 + 3"));

    EXPECT_EQ("id:foo = ((const:1 * const:2) / const:3)", parse("var foo = 1 * 2 / 3"));
    EXPECT_EQ("id:foo = ((const:1 / const:2) * const:3)", parse("var foo = 1 / 2 * 3"));
}
