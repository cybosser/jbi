#ifndef JBI_INTERPRETER_INTERPRETER_H
#define JBI_INTERPRETER_INTERPRETER_H

#include <jbi/interpreter/iterminal.h>
#include <jbi/interpreter/symbol_table.h>

namespace jbi
{

    class interpreter
    {
    private:
        std::shared_ptr<symbol_table>   _symbols;
        std::shared_ptr<iterminal>      _terminal;

    public:
        explicit interpreter(std::shared_ptr<iterminal> terminal);

        value interpret(const std::string& statement);
    };

}

#endif
