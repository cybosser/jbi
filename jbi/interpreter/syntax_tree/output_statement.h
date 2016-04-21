#ifndef JBI_INTERPRETER_SYNTAX_TREE_OUTPUT_STATEMENT_H
#define JBI_INTERPRETER_SYNTAX_TREE_OUTPUT_STATEMENT_H

#include <jbi/interpreter/syntax_tree/expression.h>
#include <jbi/interpreter/syntax_tree/statement.h>

#include <memory>

namespace jbi
{

    class output_statement : public statement
    {
    private:
        std::unique_ptr<expression> _value;

    public:
        explicit output_statement(std::unique_ptr<expression> value)
            : _value(std::move(value))
        {
            JBI_THROW_IF(!_value, argument_exception("value"));
        }

        const std::unique_ptr<expression>& value() const noexcept { return _value; }

        virtual std::string to_string() const override
        {
            return jbi::to_string(*_value);
        }

        JBI_DEFINE_VISITABLE(output_statement)
    };

}

#endif
