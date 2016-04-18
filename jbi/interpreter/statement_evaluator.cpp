#include <jbi/interpreter/statement_evaluator.h>

#include <jbi/core/exceptions.h>

namespace jbi
{

    void statement_evaluator::evaluate(const std::unique_ptr<statement>& statement)
    {
        JBI_THROW(not_implemented_exception());
    }

}