#ifndef JBI_INTERPRETER_EVALUATOR_DETAIL_ARITHMETIC_OPERATION_PERFORMER_H
#define JBI_INTERPRETER_EVALUATOR_DETAIL_ARITHMETIC_OPERATION_PERFORMER_H

#include <jbi/interpreter/arithmetic_operation.h>
#include <jbi/interpreter/exceptions.h>
#include <jbi/interpreter/types/value.h>

namespace jbi
{
    namespace detail
    {

        class arithmetic_operation_performer : public static_visitor<value>
        {
        private:
            arithmetic_operation _operation;

        public:
            explicit arithmetic_operation_performer(arithmetic_operation operation)
                : _operation(std::move(operation))
            { }

            template < typename T, typename U >
            enable_if_t<is_arithmetic<T, U>::value, value> operator()(const T& left, const U& right) const
            {
                return _operation.apply(left, right);
            };

            template < typename T, typename U >
            enable_if_t<!is_arithmetic<T, U>::value, value> operator()(const T&, const U&) const
            {
                JBI_THROW(type_exception("Unsupported operand types for " + to_string(_operation)));
            };
        };

    }
}

#endif
