#include <gtest/gtest.h>

#include <jbi/interpreter/exceptions.h>
#include <jbi/interpreter/syntactic_analyser.h>
#include <jbi/interpreter/syntax_tree/visitor.h>
#include <jbi/visitor/accept_visitor.h>

struct lispifier : public jbi::syntax_tree_visitor<std::string>
{
    std::string operator()(const jbi::arithmetic_operator& op) const
    {
        return "(" + jbi::to_string(op.operation()) + " " + jbi::accept_visitor(*this, *op.left()) + " " + jbi::accept_visitor(*this, *op.right()) + ")";
    }

    std::string operator()(const jbi::output_statement& out) const
    {
        return "(out " + jbi::accept_visitor(*this, *out.value()) + ")";
    }

    std::string operator()(const jbi::declaration_statement& var) const
    {
        return "(var " + var.identifier() + " " + jbi::accept_visitor(*this, *var.initializer()) + ")";
    }

    template < typename T >
    std::string operator()(const jbi::numeric_literal<T>& literal) const
    {
        return jbi::to_string(literal.value());
    }

    std::string operator()(const jbi::identifier& identifier) const
    {
        return identifier.name();
    }
};


std::string lispify(const std::string& statement)
{
    // TODO mock lexical_analyser
    jbi::syntactic_analyser parser{ jbi::lexical_analyser(statement) };
    return jbi::accept_visitor(lispifier(), *parser.parse());
}

TEST(syntactic_analyser_tests, assignment_statement_test)
{
    EXPECT_EQ("(var foo a)", lispify("var foo = a"));

    EXPECT_THROW(lispify("var"), jbi::syntax_exception);
    EXPECT_THROW(lispify("var * = a"), jbi::syntax_exception);
    EXPECT_THROW(lispify("var 1 = a"), jbi::syntax_exception);
    EXPECT_THROW(lispify("var out = a"), jbi::syntax_exception);
}

TEST(syntactic_analyser_tests, output_statement_test)
{
    EXPECT_EQ("(out (+ a b))", lispify("out a + b"));

    EXPECT_THROW(lispify("out"), jbi::syntax_exception);
    EXPECT_THROW(lispify("out var"), jbi::syntax_exception);
}

TEST(syntactic_analyser_tests, literals_test)
{
    EXPECT_EQ("(var foo (+ 1948 3.14))", lispify("var foo = 1948 + 3.14"));

    EXPECT_THROW(lispify("var foo = \"foo\""), jbi::syntax_exception);
}

TEST(syntactic_analyser_tests, associativity_test)
{
    EXPECT_EQ("(var foo (- (+ a b) c))", lispify("var foo = a + b - c"));
    EXPECT_EQ("(var foo (+ (- a b) c))", lispify("var foo = a - b + c"));

    EXPECT_EQ("(var foo (/ (* a b) c))", lispify("var foo = a * b / c"));
    EXPECT_EQ("(var foo (* (/ a b) c))", lispify("var foo = a / b * c"));
}

TEST(syntactic_analyser_tests, precedence_test)
{
    EXPECT_EQ("(var foo (+ a (* b c)))", lispify("var foo = a + b * c"));
    EXPECT_EQ("(var foo (+ a (/ b c)))", lispify("var foo = a + b / c"));
    EXPECT_EQ("(var foo (- a (* b c)))", lispify("var foo = a - b * c"));
    EXPECT_EQ("(var foo (- a (/ b c)))", lispify("var foo = a - b / c"));
}

TEST(syntactic_analyser_tests, parentheses_test)
{
    EXPECT_EQ("(var foo (/ (* a (- b c)) d))", lispify("var foo = (a * (b - c)) / d"));

    EXPECT_THROW(lispify("var foo = a + (b * c"), jbi::syntax_exception);
}
