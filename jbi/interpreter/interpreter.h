#ifndef JBI_INTERPRETER_INTERPRETER_H
#define JBI_INTERPRETER_INTERPRETER_H

#include <jbi/interpreter/value.h>

#include <string>

namespace jbi
{

    class interpreter
    {
    public:
        value interpret(const std::string& statement);
    };

}

#endif
