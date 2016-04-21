#include <gtest/gtest.h>

#include <jbi/interpreter/syntactic_analyser.h>
#include <jbi/interpreter/syntax_tree/visitor.h>
#include <jbi/visitor/accept_visitor.h>

struct lisp_generator : public jbi::syntax_tree_visitor<std::string>
{
    std::string operator()(const jbi::arithmetic_operator& op)
    {
        return "(" + jbi::to_string(op.operation()) + " " + jbi::accept_visitor(*this, *op.left()) + " " + jbi::accept_visitor(*this, *op.right()) + ")";
    }

    std::string operator()(const jbi::output_statement& out)
    {
        return "(out " + jbi::accept_visitor(*this, *out.value()) + ")";
    }

    std::string operator()(const jbi::assignment_statement& var)
    {
        return "(var " + var.identifier() + " " + jbi::accept_visitor(*this, *var.initializer()) + ")";
    }

    template < typename T >
    std::string operator()(const jbi::numeric_literal<T>& literal)
    {
        return jbi::to_string(literal.value());
    }
};


std::string parse(const std::string& statement)
{
    // TODO mock lexical_analyser
    jbi::syntactic_analyser parser{ jbi::lexical_analyser(statement) };

    lisp_generator generator;
    return jbi::accept_visitor(generator, *parser.parse());
}

TEST(syntactic_analyser_tests, assignment_statement_test)
{
    EXPECT_EQ("(var foo 1)", parse("var foo = 1"));

    EXPECT_THROW(parse("var * = 1"), jbi::syntax_exception);
    EXPECT_THROW(parse("var 1 = 1"), jbi::syntax_exception);
    EXPECT_THROW(parse("var out = 1"), jbi::syntax_exception);
}

TEST(syntactic_analyser_tests, associativity_test)
{
    EXPECT_EQ("(var foo (- (+ 1 2) 3))", parse("var foo = 1 + 2 - 3"));
    EXPECT_EQ("(var foo (+ (- 1 2) 3))", parse("var foo = 1 - 2 + 3"));

    EXPECT_EQ("(var foo (/ (* 1 2) 3))", parse("var foo = 1 * 2 / 3"));
    EXPECT_EQ("(var foo (* (/ 1 2) 3))", parse("var foo = 1 / 2 * 3"));
}
