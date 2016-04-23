#ifndef JBI_INTERPRETER_STATEMENT_EVALUATOR_H
#define JBI_INTERPRETER_STATEMENT_EVALUATOR_H

#include <jbi/interpreter/syntax_tree/statement.h>
#include <jbi/interpreter/symbol_table.h>

#include <memory>

namespace jbi
{

    class statement_evaluator
    {
    private:
        std::shared_ptr<symbol_table> _symbols;

    public:
        explicit statement_evaluator(std::shared_ptr<symbol_table> symbols);

        value evaluate(const std::unique_ptr<statement>& statement);
    };

}

#endif
