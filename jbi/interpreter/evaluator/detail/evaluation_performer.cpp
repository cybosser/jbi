#include <jbi/interpreter/evaluator/detail/evaluation_performer.h>

#include <jbi/interpreter/evaluator/detail/arithmetic_operation_performer.h>
#include <jbi/interpreter/evaluator/detail/value_printer.h>
#include <jbi/visitor/accept_visitor.h>

namespace jbi
{
    namespace detail
    {

        evaluation_performer::evaluation_performer(std::shared_ptr<iterminal> terminal)
            : _terminal(move(terminal))
        {
            JBI_THROW_IF(!_terminal, jbi::argument_exception("terminal"));
        }

        value evaluation_performer::operator()(const jbi::declaration_statement& var)
        {
            _symbols.set(var.identifier(), accept_visitor(*this, *var.initializer()));
            return none;
        }

        value evaluation_performer::operator()(const jbi::output_statement& out)
        {
            apply_visitor(value_printer(_terminal), accept_visitor(*this, *out.value()));
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
            JBI_THROW_IF(!_symbols.contains(id.name()), jbi::name_exception(id.name()));
            return _symbols.get(id.name());
        }

    }
}