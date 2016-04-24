#ifndef JBI_INTERPRETER_STATEMENT_EVALUATOR_H
#define JBI_INTERPRETER_STATEMENT_EVALUATOR_H

#include <jbi/interpreter/iterminal.h>
#include <jbi/interpreter/symbol_table.h>
#include <jbi/interpreter/syntax_tree/statement.h>

#include <memory>

namespace jbi
{

    class statement_evaluator
    {
    private:
        std::shared_ptr<symbol_table>   _symbols;
        std::shared_ptr<iterminal>      _terminal;

    public:
        statement_evaluator(std::shared_ptr<symbol_table> symbols, std::shared_ptr<iterminal> terminal);

        value evaluate(const std::unique_ptr<statement>& statement);
    };

}

#endif
