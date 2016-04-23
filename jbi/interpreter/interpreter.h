#ifndef JBI_INTERPRETER_INTERPRETER_H
#define JBI_INTERPRETER_INTERPRETER_H

#include <jbi/interpreter/symbol_table.h>

namespace jbi
{

    class interpreter
    {
    private:
        std::shared_ptr<symbol_table> _symbols;

    public:
        interpreter();

        value interpret(const std::string& statement);
    };

}

#endif
