#include <jbi/interpreter/interpreter.h>

#include <jbi/interpreter/syntactic_analyser.h>
#include <jbi/visitor/accept_visitor.h>

namespace jbi
{

    interpreter::interpreter(std::shared_ptr<iterminal> terminal)
        : _evaluator(std::move(terminal))
    { }

    void interpreter::interpret(const std::string& statement)
    {
        syntactic_analyser parser{ lexical_analyser(statement) };
        accept_visitor(_evaluator, *parser.parse());
    }

}
