#include <jbi/interpreter/evaluator/evaluator.h>

#include <jbi/visitor/accept_visitor.h>

namespace jbi
{

    evaluator::evaluator(std::shared_ptr<iterminal> terminal)
        : _performer(std::move(terminal))
    { }

    void evaluator::evaluate(const std::unique_ptr<statement>& statement)
    {
        JBI_THROW_IF(!statement, argument_exception("statement"));
        accept_visitor(_performer, *statement);
    }

}
