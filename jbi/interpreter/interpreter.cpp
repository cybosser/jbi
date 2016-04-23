#include <jbi/interpreter/interpreter.h>

#include <jbi/interpreter/statement_evaluator.h>
#include <jbi/interpreter/syntactic_analyser.h>

namespace jbi
{

    interpreter::interpreter()
        : _symbols(std::make_shared<symbol_table>())
    { }

    value interpreter::interpret(const std::string& statement_)
    {
        syntactic_analyser parser{ lexical_analyser(statement_) };

        const std::unique_ptr<statement> statement = parser.parse();

        statement_evaluator evaluator(_symbols);

        return evaluator.evaluate(statement);
    }

}
