#ifndef JBI_INTERPRETER_SYNTAX_TREE_VISITOR_H
#define JBI_INTERPRETER_SYNTAX_TREE_VISITOR_H

#include <jbi/interpreter/syntax_tree/arithmetic_operator.h>
#include <jbi/interpreter/syntax_tree/declaration_statement.h>
#include <jbi/interpreter/syntax_tree/identifier.h>
#include <jbi/interpreter/syntax_tree/input_statement.h>
#include <jbi/interpreter/syntax_tree/literals.h>
#include <jbi/interpreter/syntax_tree/output_statement.h>
#include <jbi/interpreter/syntax_tree/range.h>
#include <jbi/visitor/visitor.h>

namespace jbi
{

    template < typename ReturnType >
    using statement_visitor = visitor<ReturnType,
        declaration_statement,
        input_statement,
        output_statement
    >;

    template < typename ReturnType >
    using expression_visitor = visitor<ReturnType,
        arithmetic_operator,
        floating_literal,
        identifier,
        integer_literal,
        range
    >;

}

#endif
