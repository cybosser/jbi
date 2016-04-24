#ifndef JBI_INTERPRETER_EVALUATOR_EVALUATOR_H
#define JBI_INTERPRETER_EVALUATOR_EVALUATOR_H

#include <jbi/interpreter/evaluator/detail/evaluation_performer.h>

namespace jbi
{

    class evaluator
    {
    private:
        detail::evaluation_performer _performer;

    public:
        explicit evaluator(std::shared_ptr<iterminal> terminal);

        void evaluate(const std::unique_ptr<statement>& statement);
    };

}

#endif
