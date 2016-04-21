#ifndef JBI_INTERPRETER_SYNTAX_TREE_ASSIGNMENT_STATEMENT_H
#define JBI_INTERPRETER_SYNTAX_TREE_ASSIGNMENT_STATEMENT_H

#include <jbi/interpreter/syntax_tree/expression.h>
#include <jbi/interpreter/syntax_tree/statement.h>

#include <memory>

namespace jbi
{

    class assignment_statement : public statement
    {
    private:
        std::string                 _identifier;
        std::unique_ptr<expression> _initializer;

    public:
        assignment_statement(std::string identifier, std::unique_ptr<expression> initializer)
            : _identifier(std::move(identifier)), _initializer(std::move(initializer))
        {
            JBI_THROW_IF(_identifier.empty(), argument_exception("identifier"));
            JBI_THROW_IF(!_initializer, argument_exception("initializer"));
        }

        const std::string& identifier() const noexcept                   { return _identifier; }
        const std::unique_ptr<expression>& initializer() const noexcept  { return _initializer; }

        std::string to_string() const override
        {
            return "id:" + _identifier + " = " + jbi::to_string(*_initializer);
        }

        JBI_DEFINE_VISITABLE(assignment_statement)
    };

}

#endif
