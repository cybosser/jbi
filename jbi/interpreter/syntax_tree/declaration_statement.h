#ifndef JBI_INTERPRETER_SYNTAX_TREE_DECLARATION_STATEMENT_H
#define JBI_INTERPRETER_SYNTAX_TREE_DECLARATION_STATEMENT_H

#include <jbi/interpreter/syntax_tree/expression.h>
#include <jbi/interpreter/syntax_tree/statement.h>

#include <memory>

namespace jbi
{

    class declaration_statement : public statement
    {
    private:
        std::string                 _identifier;
        std::unique_ptr<expression> _initializer;

    public:
        declaration_statement(std::string identifier, std::unique_ptr<expression> initializer)
            : _identifier(std::move(identifier)), _initializer(std::move(initializer))
        {
            JBI_THROW_IF(_identifier.empty(), argument_exception("identifier"));
            JBI_THROW_IF(!_initializer, argument_exception("initializer"));
        }

        const std::string& identifier() const noexcept                   { return _identifier; }
        const std::unique_ptr<expression>& initializer() const noexcept  { return _initializer; }

        JBI_DEFINE_VISITABLE(declaration_statement)
    };

}

#endif
