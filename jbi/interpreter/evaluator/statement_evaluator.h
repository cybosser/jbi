#ifndef JBI_INTERPRETER_EVALUATOR_STATEMENT_EVALUATOR_H
#define JBI_INTERPRETER_EVALUATOR_STATEMENT_EVALUATOR_H

#include <jbi/interpreter/evaluator/expression_evaluator.h>
#include <jbi/interpreter/evaluator/value_printer.h>

namespace jbi
{

    class statement_evaluator : public statement_visitor<void>
    {
    private:
        std::shared_ptr<symbol_table>   _symbols;
        expression_evaluator            _evaluator;
        std::shared_ptr<iterminal>      _terminal;
        value_printer                   _printer;

    public:
        explicit statement_evaluator(std::shared_ptr<iterminal> terminal);

        void operator()(const declaration_statement& var);
        void operator()(const output_statement& out);
        void operator()(const input_statement& in);
    };

}

#endif
