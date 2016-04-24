#include <jbi/interpreter/interpreter.h>

#include <jbi/interpreter/statement_evaluator.h>
#include <jbi/interpreter/syntactic_analyser.h>

namespace jbi
{

    interpreter::interpreter(std::shared_ptr<iterminal> terminal)
        : _evaluator(terminal)
    { }

    void interpreter::interpret(const std::string& statement)
    {
        lexical_analyser tokenizer(statement);
        syntactic_analyser parser(std::move(tokenizer));

        _evaluator.evaluate(parser.parse());
    }

}
