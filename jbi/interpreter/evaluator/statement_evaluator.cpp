#include <jbi/interpreter/evaluator/statement_evaluator.h>

#include <jbi/interpreter/string.h>
#include <jbi/visitor/accept_visitor.h>

namespace jbi
{

    statement_evaluator::statement_evaluator(std::shared_ptr<iterminal> terminal)
        : _symbols(std::make_shared<symbol_table>()), _evaluator(_symbols), _terminal(move(terminal)), _printer(_terminal)
    {
        JBI_THROW_IF(!_terminal, argument_exception("terminal"));
    }

    void statement_evaluator::operator()(const declaration_statement& var)
    {
        JBI_THROW_IF(_symbols->contains(var.identifier()), name_exception("Variable '" + var.identifier() + "' is already declared"));
        _symbols->set(var.identifier(), accept_visitor(_evaluator, *var.initializer()));
    }

    void statement_evaluator::operator()(const output_statement& out)
    {
        apply_visitor(_printer, accept_visitor(_evaluator, *out.value()));
    }

    void statement_evaluator::operator()(const input_statement& in)
    {
        JBI_THROW_IF(_symbols->contains(in.identifier()), name_exception("Variable '" + in.identifier() + "' is already declared"));
        _symbols->set(in.identifier(), from_string<int>(_terminal->read_line()));
    }

}