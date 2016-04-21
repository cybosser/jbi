#ifndef JBI_INTERPRETER_STATEMENT_EVALUATOR_H
#define JBI_INTERPRETER_STATEMENT_EVALUATOR_H

#include <jbi/interpreter/syntax_tree/statement.h>

#include <memory>

namespace jbi
{

    class statement_evaluator
    {
    public:
        void evaluate(const std::unique_ptr<statement>& statement);
    };

}

#endif
