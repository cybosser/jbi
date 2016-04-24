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

TEST_F(interpreter_tests, out_test)
{
    EXPECT_CALL(*terminal, write_line("1987.14"));

    interpreter.interpret("out 1984 + 3.14");
}

TEST_F(interpreter_tests, invalid_name_test)
{
    EXPECT_THROW(interpreter.interpret("out foo"), jbi::name_exception);
}

TEST_F(interpreter_tests, var_test)
{
    EXPECT_CALL(*terminal, write_line("1987.14"));

    interpreter.interpret("var foo = 1984 + 3.14");
    interpreter.interpret("out foo");
}