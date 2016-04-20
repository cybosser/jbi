#ifndef JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_LITERALS_H
#define JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_LITERALS_H

#include <jbi/interpreter/abstract_syntax_tree/expression.h>

namespace jbi
{

    namespace detail
    {

        template < typename T >
        class literal : public expression
        {
        private:
            T _value;

        public:
            explicit literal(T value) noexcept
                : _value(value)
            { }

            T value() const noexcept { return _value; }
        };

    }

    using integer_literal = detail::literal<int>;
    using floating_point_literal = detail::literal<double>;

}

#endif
