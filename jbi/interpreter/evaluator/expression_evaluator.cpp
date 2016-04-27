#include <jbi/interpreter/evaluator/expression_evaluator.h>

#include <jbi/visitor/accept_visitor.h>

namespace jbi
{

    namespace
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


        class numeric_range_builder : public static_visitor<numeric_range<int>>
        {
        public:
            numeric_range<int> operator()(int start, int stop) const
            {
                JBI_THROW_IF(start > stop, value_exception("Invalid range end"));
                return numeric_range<int>(start, stop);
            }

            template < typename T, typename U >
            numeric_range<int> operator()(const T&, const U&) const
            {
                JBI_THROW(type_exception("Invalid type of range begin/end"));
            };
        };

    }


    expression_evaluator::expression_evaluator(std::shared_ptr<symbol_table> symbols)
        : _symbols(std::move(symbols))
    { }

    value expression_evaluator::operator()(const arithmetic_operator& op)
    {
        return apply_visitor(arithmetic_operation_performer(op.operation()),
            accept_visitor(*this, *op.left()), accept_visitor(*this, *op.right())
        );
    }

    value expression_evaluator::operator()(const identifier& id) const
    {
        JBI_THROW_IF(!_symbols->contains(id.name()), name_exception("Variable '" + id.name() + "' is not declared"));
        return _symbols->get(id.name());
    }

    value expression_evaluator::operator()(const range& range)
    {
        return apply_visitor(numeric_range_builder(),
            accept_visitor(*this, *range.start()), accept_visitor(*this, *range.stop())
        );
    }

}