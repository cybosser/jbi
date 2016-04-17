#include <gtest/gtest.h>

#include <jbi/interpreter/lexer/lexer.h>

class lexer_tester
{
private:
    jbi::lexer  _lexer;

public:
    explicit lexer_tester(const std::string& statement)
        : _lexer(statement)
    { }

    ~lexer_tester()
    {
        expect(jbi::token::eof());
    }

    void expect(const jbi::token& expected)
    {
        EXPECT_EQ(expected, _lexer.read_token());
    }
};

TEST(lexer_tests, keywords_test)
{
    lexer_tester tester("var in out print");

    tester.expect(jbi::token::var());
    tester.expect(jbi::token::in());
    tester.expect(jbi::token::out());
    tester.expect(jbi::token::print());
}

TEST(lexer_tests, identifiers_test)
{
    lexer_tester tester("a foo b2");

    tester.expect(jbi::token::identifier("a"));
    tester.expect(jbi::token::identifier("foo"));
    tester.expect(jbi::token::identifier("b2"));
}

TEST(lexer_tests, numbers_test)
{
    lexer_tester tester("7 42 1984 3.14 0.5 9.");

    tester.expect(jbi::token::number(7));
    tester.expect(jbi::token::number(42));
    tester.expect(jbi::token::number(1984));
    tester.expect(jbi::token::number(3.14));
    tester.expect(jbi::token::number(0.5));
    tester.expect(jbi::token::number(9.0));
}

TEST(lexer_tests, symbols_test)
{
    lexer_tester tester("= , + - / * ^ {} ( )");

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

TEST(lexer_tests, arrow_test)
{
    lexer_tester tester("->");

    tester.expect(jbi::token::arrow());
}

TEST(lexer_tests, invalid_symbols_test)
{
    jbi::lexer lexer("%foo");
    EXPECT_THROW(lexer.read_token(), jbi::syntax_exception);
}
