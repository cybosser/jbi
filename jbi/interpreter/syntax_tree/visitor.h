#ifndef JBI_INTERPRETER_SYNTAX_TREE_VISITOR_H
#define JBI_INTERPRETER_SYNTAX_TREE_VISITOR_H

#include <jbi/interpreter/syntax_tree/arithmetic_operator.h>
#include <jbi/interpreter/syntax_tree/declaration_statement.h>
#include <jbi/interpreter/syntax_tree/identifier.h>
#include <jbi/interpreter/syntax_tree/input_statement.h>
#include <jbi/interpreter/syntax_tree/literals.h>
#include <jbi/interpreter/syntax_tree/output_statement.h>
#include <jbi/visitor/visitor.h>

namespace jbi
{

    template < typename ReturnType >
    using syntax_tree_visitor = visitor<ReturnType,
        arithmetic_operator,
        declaration_statement,
        floating_literal,
        identifier,
        input_statement,
        integer_literal,
        output_statement
    >;
}

#endif
