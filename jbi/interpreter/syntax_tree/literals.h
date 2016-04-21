#ifndef JBI_INTERPRETER_SYNTAX_TREE_LITERALS_H
#define JBI_INTERPRETER_SYNTAX_TREE_LITERALS_H

#include <jbi/interpreter/syntax_tree/expression.h>

namespace jbi
{

    template < typename T >
    class numeric_literal : public expression
    {
    private:
        T _value;

    public:
        explicit numeric_literal(T value) noexcept
            : _value(value)
        { }

        T value() const noexcept { return _value; }

        virtual std::string to_string() const override
        {
            return "const:" + jbi::to_string(_value);
        }

        JBI_DEFINE_VISITABLE(numeric_literal)
    };

    using integer_literal = numeric_literal<int>;
    using floating_point_literal = numeric_literal<double>;

}

#endif
