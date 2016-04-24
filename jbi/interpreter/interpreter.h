#ifndef JBI_INTERPRETER_INTERPRETER_H
#define JBI_INTERPRETER_INTERPRETER_H

#include <jbi/interpreter/evaluator.h>

namespace jbi
{

    class interpreter
    {
    private:
        evaluator _evaluator;

    public:
        explicit interpreter(std::shared_ptr<iterminal> terminal);

        void interpret(const std::string& statement);
    };

}

#endif
