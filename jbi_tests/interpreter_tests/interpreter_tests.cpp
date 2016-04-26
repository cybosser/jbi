#include <gmock/gmock.h>

#include <jbi/interpreter/interpreter.h>
#include <jbi/interpreter/exceptions.h>

class interpreter_tests : public ::testing::Test
{
protected:
    struct mock_terminal : public jbi::iterminal
    {
        MOCK_METHOD0(read_line, std::string());
        MOCK_METHOD1(write_line, void(const std::string&));
    };

    interpreter_tests()
        : terminal(std::make_shared<mock_terminal>()), interpreter(terminal)
    { }

    std::shared_ptr<mock_terminal>  terminal;
    jbi::interpreter                interpreter;
};

TEST_F(interpreter_tests, output_test)
{
    EXPECT_CALL(*terminal, write_line("1987.14"));

    interpreter.interpret("out 1984 + 3.14");
}

TEST_F(interpreter_tests, undeclared_variable_output_test)
{
    EXPECT_THROW(interpreter.interpret("out foo"), jbi::name_exception);
}

TEST_F(interpreter_tests, input_test)
{
    using namespace ::testing;

    EXPECT_CALL(*terminal, read_line()).WillOnce(Return("1948"));
    EXPECT_CALL(*terminal, write_line("1948"));

    interpreter.interpret("in foo");
    interpreter.interpret("out foo");
}

TEST_F(interpreter_tests, declared_variable_input_test)
{
    using namespace ::testing;

    EXPECT_CALL(*terminal, read_line()).WillOnce(Return("1948"));

    interpreter.interpret("in foo");

    EXPECT_THROW(interpreter.interpret("in foo"), jbi::name_exception);
}


TEST_F(interpreter_tests, variable_declaration_test)
{
    EXPECT_CALL(*terminal, write_line("1987.14"));

    interpreter.interpret("var foo = 1984 + 3.14");
    interpreter.interpret("out foo");
}

TEST_F(interpreter_tests, declared_variable_declaration_test)
{
    interpreter.interpret("var foo = 1");

    EXPECT_THROW(interpreter.interpret("var foo = 2"), jbi::name_exception);
}

TEST_F(interpreter_tests, arithmetic_test)
{
    using namespace ::testing;

    {
        InSequence sequence;

        EXPECT_CALL(*terminal, write_line("13"));
        EXPECT_CALL(*terminal, write_line("18.5"));
        EXPECT_CALL(*terminal, write_line("22.14"));
        EXPECT_CALL(*terminal, write_line("512"));
        EXPECT_CALL(*terminal, write_line("515"));
    }

    interpreter.interpret("out 8 - 42 * 0.5 / (10 - 3) + 2 ^ 3");
    interpreter.interpret("out (25.0 - 7) / 2 * 3 - 8.5");
    interpreter.interpret("out 3.14 + 2 * (16 - 9) + 8 - 2 - 1");
    interpreter.interpret("out 2 ^ 3 ^ 2");
    interpreter.interpret("out 2 ^ 3 ^ 2 + 3");
}

TEST_F(interpreter_tests, division_by_zero_test)
{
    using namespace ::testing;

    EXPECT_CALL(*terminal, write_line(_)).Times(2);

    EXPECT_THROW(interpreter.interpret("out 1 / 0"), jbi::arithmetic_exception);
    EXPECT_NO_THROW(interpreter.interpret("out 1.0 / 0"));
    EXPECT_NO_THROW(interpreter.interpret("out 1 / 0.0"));
}

TEST_F(interpreter_tests, range_test)
{
    EXPECT_CALL(*terminal, write_line("[0, 1)"));

    interpreter.interpret("out { 6 - 3 * 2, 4 / 4 }");
}

TEST_F(interpreter_tests, invalid_range_test)
{
    EXPECT_THROW(interpreter.interpret("out { , 1 }"), jbi::syntax_exception);
    EXPECT_THROW(interpreter.interpret("out { 0, }"), jbi::syntax_exception);
    EXPECT_THROW(interpreter.interpret("out { 0 1 }"), jbi::syntax_exception);

    EXPECT_THROW(interpreter.interpret("out { 0.0, 1 }"), jbi::type_exception);
    EXPECT_THROW(interpreter.interpret("out { 0, 1.0 }"), jbi::type_exception);

    EXPECT_THROW(interpreter.interpret("out { 1, 0 }"), jbi::value_exception);
    EXPECT_THROW(interpreter.interpret("out { 0, 0 }"), jbi::value_exception);
}
