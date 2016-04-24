#include <jbi/interpreter/evaluator.h>

#include <jbi/interpreter/exceptions.h>
#include <jbi/interpreter/syntax_tree/visitor.h>
#include <jbi/visitor/accept_visitor.h>

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


        class value_printer : public static_visitor<>
        {
        private:
            std::shared_ptr<iterminal> _terminal;

        public:
            explicit value_printer(std::shared_ptr<iterminal> terminal)
                : _terminal(std::move(terminal))
            {
                JBI_THROW_IF(!_terminal, argument_exception("terminal"));
            }

            template < typename T >
            void operator()(const T& value)
            {
                _terminal->write_line(to_string(value));
            }

            void operator()(none_t)
            { }
        };


        class evaluation_performer : public syntax_tree_visitor<value>
        {
        private:
            std::shared_ptr<symbol_table>   _symbols;
            std::shared_ptr<iterminal>      _terminal;

        public:
            explicit evaluation_performer(std::shared_ptr<symbol_table> symbols, std::shared_ptr<iterminal> terminal)
                : _symbols(std::move(symbols)), _terminal(std::move(terminal))
            {
                JBI_THROW_IF(!_symbols, argument_exception("symbols"));
                JBI_THROW_IF(!_terminal, argument_exception("terminal"));
            }

            value operator()(const arithmetic_operator& op)
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

            value operator()(const assignment_statement& var)
            {
                _symbols->set(var.identifier(), accept_visitor(*this, *var.initializer()));
                return none;
            }

            value operator()(const identifier& id) const
            {
                const std::string& name = id.name();
                JBI_THROW_IF(!_symbols->contains(name), name_exception(name));
                return _symbols->get(name);
            }

            value operator()(const output_statement& out)
            {
                apply_visitor(value_printer(_terminal), accept_visitor(*this, *out.value()));
                return none;
            }
        };

    }

    evaluator::evaluator(std::shared_ptr<iterminal> terminal)
        : _symbols(std::make_shared<symbol_table>()), _terminal(std::move(terminal))
    {
        JBI_THROW_IF(!_terminal, argument_exception("terminal"));
    }

    void evaluator::evaluate(const std::unique_ptr<statement>& statement)
    {
        JBI_THROW_IF(!statement, argument_exception("statement"));
        accept_visitor(detail::evaluation_performer(_symbols, _terminal), *statement);
    }

}
