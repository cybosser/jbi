#ifndef JBI_INTERPRETER_SYNTAX_TREE_INPUT_STATEMENT_H
#define JBI_INTERPRETER_SYNTAX_TREE_INPUT_STATEMENT_H

#include <jbi/core/exceptions.h>
#include <jbi/interpreter/syntax_tree/statement.h>
#include <jbi/visitor/visitable.h>

namespace jbi
{

    class input_statement : public statement
    {
    private:
        std::string _identifier;

    public:
        explicit input_statement(std::string identifier)
            : _identifier(std::move(identifier))
        {
            JBI_THROW_IF(_identifier.empty(), argument_exception("identifier"));
        }

        const std::string& identifier() const noexcept { return _identifier; }

        JBI_DEFINE_VISITABLE(input_statement)
    };

}

#endif
