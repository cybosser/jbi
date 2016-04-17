#ifndef JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_OUTPUT_STATEMENT_H
#define JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_OUTPUT_STATEMENT_H

#include <jbi/interpreter/abstract_syntax_tree/expression.h>

#include <memory>

namespace jbi
{

    class output_statement
    {
    private:
        std::unique_ptr<expression> _value;

    public:
        output_statement(std::unique_ptr<expression> value)
            : _value(std::move(value))
        { }

        const std::unique_ptr<expression>& value() const { return _value; }
    };

}

#endif
