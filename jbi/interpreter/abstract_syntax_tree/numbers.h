#ifndef JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_NUMBERS_H
#define JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_NUMBERS_H

#include <jbi/interpreter/abstract_syntax_tree/expression.h>

namespace jbi
{

    namespace detail
    {

        template < typename T >
        class number : public expression
        {
        private:
            T _value;

        public:
            explicit number(T value)
                : _value(value)
            { }

            T value() const { return _value; }
        };

    }

    using integer_number = detail::number<int>;
    using floating_point_number = detail::number<double>;

}

#endif
