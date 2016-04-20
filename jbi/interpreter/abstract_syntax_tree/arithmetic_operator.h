#ifndef JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_ARITHMETIC_OPERATOR
#define JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_ARITHMETIC_OPERATOR

#include <jbi/interpreter/abstract_syntax_tree/expression.h>
#include <jbi/interpreter/arithmetic_operation.h>

#include <memory>

namespace jbi
{

    class arithmetic_operator : public expression
    {
    private:
        arithmetic_operation        _operation;

        std::unique_ptr<expression> _left;
        std::unique_ptr<expression> _right;

    public:
        arithmetic_operator(arithmetic_operation operation, std::unique_ptr<expression> left, std::unique_ptr<expression> right) noexcept
            : _operation(operation), _left(std::move(left)), _right(std::move(right))
        { }

        arithmetic_operation operation() const noexcept { return _operation; }

        const std::unique_ptr<expression>& left() const noexcept  { return _left; }
        const std::unique_ptr<expression>& right() const noexcept { return _right; }

        virtual std::string to_string() const override
        {
            return "(" + jbi::to_string(*_left) + " " + jbi::to_string(_operation) + " " + jbi::to_string(*_right) + ")";
        }
    };

}

#endif
