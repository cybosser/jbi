#ifndef JBI_INTERPRETER_SYNTAX_TREE_VISITOR_H
#define JBI_INTERPRETER_SYNTAX_TREE_VISITOR_H

#include <jbi/interpreter/syntax_tree/arithmetic_operator.h>
#include <jbi/interpreter/syntax_tree/assignment_statement.h>
#include <jbi/interpreter/syntax_tree/identifier.h>
#include <jbi/interpreter/syntax_tree/literals.h>
#include <jbi/interpreter/syntax_tree/output_statement.h>
#include <jbi/visitor/visitor.h>

namespace jbi
{

    template < typename ReturnType >
    using syntax_tree_visitor = visitor<ReturnType,
        arithmetic_operator,
        assignment_statement,
        floating_literal,
        identifier,
        integer_literal,
        output_statement
    >;
}

#endif
