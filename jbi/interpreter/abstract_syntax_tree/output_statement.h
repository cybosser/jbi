#ifndef JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_OUTPUT_STATEMENT_H
#define JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_OUTPUT_STATEMENT_H

#include <jbi/interpreter/abstract_syntax_tree/expression.h>
#include <jbi/interpreter/abstract_syntax_tree/statement.h>

#include <memory>

namespace jbi
{

    class output_statement : public statement
    {
    private:
        std::unique_ptr<expression> _expression;

    public:
        output_statement(std::unique_ptr<expression> expression) noexcept
            : _expression(std::move(expression))
        { }

        const std::unique_ptr<expression>& value() const noexcept { return _expression; }

        virtual std::string to_string() const override
        {
            return jbi::to_string(*_expression);
        }
    };

}

#endif