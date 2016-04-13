#ifndef JBI_INTERPRETER_INTERPRETER_H
#define JBI_INTERPRETER_INTERPRETER_H

#include <jbi/variant/variant.h>

#include <string>

namespace jbi
{

    using value = variant<int, float>;

    class interpreter
    {
    public:
        value interpret(const std::string& statement);
    };

}

#endif
