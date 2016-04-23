#include <jbi/interpreter/statement_evaluator.h>

#include <jbi/interpreter/exceptions.h>
#include <jbi/interpreter/syntax_tree/visitor.h>
#include <jbi/visitor/accept_visitor.h>

namespace jbi
{

    namespace detail
    {

        class arithmetic_operation_performer : public static_visitor<value>
        {
            template < typename T, typename U >
            using is_arithmetic = bool_constant<std::is_arithmetic<T>::value && std::is_arithmetic<U>::value>;

        private:
            arithmetic_operation _operation;

        public:
            explicit arithmetic_operation_performer(arithmetic_operation operation)
                : _operation(std::move(operation))
            { }

            template < typename T, typename U >
            enable_if_t<is_arithmetic<T, U>::value, value> operator()(const T& left, const U& right) const
            {
                if (_operation == arithmetic_operation::addition())
                    return left + right;

                if (_operation == arithmetic_operation::subtraction())
                    return left - right;

                if (_operation == arithmetic_operation::multiplication())
                    return left * right;

                if (_operation == arithmetic_operation::division())
                    return left / right;

                JBI_THROW(not_implemented_exception());
            };

            template < typename T, typename U >
            enable_if_t<!is_arithmetic<T, U>::value, value> operator()(const T&, const U&) const
            {
                JBI_THROW(type_exception("Unsupported operand types for " + to_string(_operation)));
            };
        };

        class evaluator : public syntax_tree_visitor<value>
        {
        public:
            value operator()(const arithmetic_operator& op) const
            {
                return apply_visitor(arithmetic_operation_performer(op.operation()),
                    accept_visitor(*this, *op.left()), accept_visitor(*this, *op.right())
                );
            }

            template < typename T >
            value operator()(const numeric_literal<T>& literal) const
            {
                return literal.value();
            }

            template < typename T >
            value operator()(const T&) const
            {
                JBI_THROW(not_implemented_exception());
            }
        };

    }

    value statement_evaluator::evaluate(const std::unique_ptr<statement>& statement)
    {
        JBI_THROW_IF(!statement, argument_exception("statement"));
        return accept_visitor(detail::evaluator(), *statement);
    }

}