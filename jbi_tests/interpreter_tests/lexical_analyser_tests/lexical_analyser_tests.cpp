#include <gtest/gtest.h>

#include <jbi/interpreter/lexical_analyser/lexical_analyser.h>

class lexical_analyser_tester
{
private:
    jbi::lexical_analyser  _analyser;

public:
    explicit lexical_analyser_tester(const std::string& statement)
        : _analyser(statement)
    { }

    ~lexical_analyser_tester()
    {
        expect(jbi::token::eof());
    }

    void expect(const jbi::token& expected)
    {
        EXPECT_EQ(expected, _analyser.read_token());
    }
};

TEST(lexical_analyser_tests, keywords_test)
{
    lexical_analyser_tester tester("var in out print");

    tester.expect(jbi::token::var());
    tester.expect(jbi::token::in());
    tester.expect(jbi::token::out());
    tester.expect(jbi::token::print());
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
    lexical_analyser_tester tester("7 42 1984 3.14 0.5 9.");

    tester.expect(jbi::token::number(7));
    tester.expect(jbi::token::number(42));
    tester.expect(jbi::token::number(1984));
    tester.expect(jbi::token::number(3.14));
    tester.expect(jbi::token::number(0.5));
    tester.expect(jbi::token::number(9.0));
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

    tester.expect(jbi::token::number(1984));
    tester.expect(jbi::token::number(3.14));
    tester.expect(jbi::token::identifier("foo"));
    tester.expect(jbi::token::identifier("bar"));
    tester.expect(jbi::token::left_parenthesis());
    tester.expect(jbi::token::right_parenthesis());
}

TEST(lexical_analyser_tests, invalid_symbols_test)
{
    jbi::lexical_analyser analyser("%foo");
    EXPECT_THROW(analyser.read_token(), jbi::syntax_exception);
}
