#ifndef JBI_INTERPRETER_SYNTAX_TREE_VISITOR_H
#define JBI_INTERPRETER_SYNTAX_TREE_VISITOR_H

#include <jbi/interpreter/syntax_tree/arithmetic_operator.h>
#include <jbi/interpreter/syntax_tree/assignment_statement.h>
#include <jbi/interpreter/syntax_tree/literals.h>
#include <jbi/interpreter/syntax_tree/output_statement.h>
#include <jbi/visitor/visitor.h>

namespace jbi
{

    template < typename ReturnType >
    using syntax_tree_visitor = visitor<ReturnType,
        arithmetic_operator,
        assignment_statement,
        output_statement,
        integer_literal,
        floating_point_literal
    >;
}

#endif
