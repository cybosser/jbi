#include <jbi/interpreter/interpreter.h>

#include <jbi/interpreter/statement_evaluator.h>
#include <jbi/interpreter/syntactic_analyser.h>

namespace jbi
{

    interpreter::interpreter(std::shared_ptr<iterminal> terminal)
        : _symbols(std::make_shared<symbol_table>()), _terminal(std::move(terminal))
    {
        JBI_THROW_IF(!_terminal, argument_exception("terminal"));
    }

    void interpreter::interpret(const std::string& statement_)
    {
        syntactic_analyser parser{ lexical_analyser(statement_) };

        const std::unique_ptr<statement> statement = parser.parse();

        statement_evaluator evaluator(_symbols, _terminal);

        evaluator.evaluate(statement);
    }

}
