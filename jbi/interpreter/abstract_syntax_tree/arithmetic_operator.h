#ifndef JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_ARITHMETIC_OPERATOR
#define JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_ARITHMETIC_OPERATOR

#include <jbi/interpreter/abstract_syntax_tree/expression.h>

#include <memory>

namespace jbi
{

    enum class arithmetic_operation
    {
        addition,
        subtraction,
        multiplication,
        division,
        exponentiation
    };


    class arithmetic_operator : public expression
    {
    private:
        arithmetic_operation        _operation;

        std::unique_ptr<expression> _left;
        std::unique_ptr<expression> _right;

    public:
        arithmetic_operator(arithmetic_operation operation, std::unique_ptr<expression> left, std::unique_ptr<expression> right)
            : _operation(operation), _left(std::move(left)), _right(std::move(right))
        { }

        arithmetic_operation operation() const { return _operation; }

        const std::unique_ptr<expression>& left() const  { return _left; }
        const std::unique_ptr<expression>& right() const { return _right; }
    };

}

#endif
