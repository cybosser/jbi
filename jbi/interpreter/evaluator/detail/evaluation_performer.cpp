#include <jbi/interpreter/evaluator/detail/evaluation_performer.h>

#include <jbi/interpreter/evaluator/detail/arithmetic_operation_performer.h>
#include <jbi/interpreter/string.h>
#include <jbi/visitor/accept_visitor.h>

namespace jbi
{
    namespace detail
    {

        evaluation_performer::evaluation_performer(std::shared_ptr<iterminal> terminal)
            : _terminal(move(terminal)), _printer(_terminal)
        {
            JBI_THROW_IF(!_terminal, jbi::argument_exception("terminal"));
        }

        value evaluation_performer::operator()(const jbi::declaration_statement& var)
        {
            expect_undeclared(var.identifier());

            _symbols.set(var.identifier(), accept_visitor(*this, *var.initializer()));

            return none;
        }

        value evaluation_performer::operator()(const jbi::output_statement& out)
        {
            apply_visitor(_printer, accept_visitor(*this, *out.value()));

            return none;
        }

        value evaluation_performer::operator()(const jbi::input_statement& in)
        {
            expect_undeclared(in.identifier());

            _symbols.set(in.identifier(), from_string<int>(_terminal->read_line()));

            return none;
        }

        value evaluation_performer::operator()(const jbi::arithmetic_operator& op)
        {
            return apply_visitor(arithmetic_operation_performer(op.operation()),
                 accept_visitor(*this, *op.left()), accept_visitor(*this, *op.right())
            );
        }

        value evaluation_performer::operator()(const jbi::identifier& id) const
        {
            expect_declared(id.name());

            return _symbols.get(id.name());
        }

        void evaluation_performer::expect_undeclared(const std::string &identifier) const
        {
            JBI_THROW_IF(_symbols.contains(identifier), jbi::name_exception("Variable '" + identifier + "' is already defined"));
        }

        void evaluation_performer::expect_declared(const std::string &identifier) const
        {
            JBI_THROW_IF(!_symbols.contains(identifier), jbi::name_exception("Variable '" + identifier + "' is not defined"));
        }
    }
}