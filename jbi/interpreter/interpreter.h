#ifndef JBI_INTERPRETER_INTERPRETER_H
#define JBI_INTERPRETER_INTERPRETER_H

#include <string>

namespace jbi
{

    class interpreter
    {
    public:
        void interpret(const std::string& statement);
    };

}

#endif
