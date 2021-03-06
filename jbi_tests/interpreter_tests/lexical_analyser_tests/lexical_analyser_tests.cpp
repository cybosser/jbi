#include <gtest/gtest.h>

#include <jbi/interpreter/exceptions.h>
#include <jbi/interpreter/lexical_analyser/lexical_analyser.h>

class lexical_analyser_tester
{
private:
    jbi::lexical_analyser  _tokenizer;

public:
    explicit lexical_analyser_tester(const std::string& statement)
        : _tokenizer(statement)
    { }

    ~lexical_analyser_tester()
    {
        expect(jbi::token::eof());
    }

    void expect(const jbi::token& expected)
    {
        EXPECT_EQ(expected, _tokenizer.read());
    }
};

TEST(lexical_analyser_tests, builtins_test)
{
    lexical_analyser_tester tester("var in out print map reduce");

    tester.expect(jbi::token::var());
    tester.expect(jbi::token::in());
    tester.expect(jbi::token::out());
    tester.expect(jbi::token::print());
    tester.expect(jbi::token::map());
    tester.expect(jbi::token::reduce());
}

TEST(lexical_analyser_tests, identifiers_test)
{
    lexical_analyser_tester tester("a foo b2");

    tester.expect(jbi::token::identifier("a"));
    tester.expect(jbi::token::identifier("foo"));
    tester.expect(jbi::token::identifier("b2"));
}

TEST(lexical_analyser_tests, numbers_test)
{
    lexical_analyser_tester tester("7 1984 3.14 9. -3 -1.62");

    tester.expect(jbi::token::literal(7));
    tester.expect(jbi::token::literal(1984));
    tester.expect(jbi::token::literal(3.14));
    tester.expect(jbi::token::literal(9.0));
    tester.expect(jbi::token::literal(-3));
    tester.expect(jbi::token::literal(-1.62));
}

TEST(lexical_analyser_tests, integer_overflow_test)
{
    jbi::lexical_analyser tokenizer(std::to_string(std::numeric_limits<unsigned int>::max()));
    EXPECT_THROW(tokenizer.read(), jbi::value_exception);
}

TEST(lexical_analyser_tests, symbols_test)
{
    lexical_analyser_tester tester("= , + - / * ^ {} ( )");

    tester.expect(jbi::token::equals());
    tester.expect(jbi::token::comma());
    tester.expect(jbi::token::plus());
    tester.expect(jbi::token::minus());
    tester.expect(jbi::token::slash());
    tester.expect(jbi::token::asterisk());
    tester.expect(jbi::token::carret());
    tester.expect(jbi::token::left_brace());
    tester.expect(jbi::token::right_brace());
    tester.expect(jbi::token::left_parenthesis());
    tester.expect(jbi::token::right_parenthesis());
}

TEST(lexical_analyser_tests, arrow_test)
{
    lexical_analyser_tester tester("->");

    tester.expect(jbi::token::arrow());
}

TEST(lexical_analyser_tests, spaces_test)
{
    lexical_analyser_tester tester("   1984\t\t3.14\n\n\nfoo\r\rbar \r(\n \r  \t)");

    tester.expect(jbi::token::literal(1984));
    tester.expect(jbi::token::literal(3.14));
    tester.expect(jbi::token::identifier("foo"));
    tester.expect(jbi::token::identifier("bar"));
    tester.expect(jbi::token::left_parenthesis());
    tester.expect(jbi::token::right_parenthesis());
}

TEST(lexical_analyser_tests, invalid_symbols_test)
{
    jbi::lexical_analyser tokenizer("%foo");
    EXPECT_THROW(tokenizer.read(), jbi::syntax_exception);
}

TEST(lexical_analyser_tests, empty_statement)
{
    jbi::lexical_analyser tokenizer("");
    EXPECT_EQ(jbi::token::eof(), tokenizer.read());
}
