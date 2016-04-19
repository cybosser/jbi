#ifndef JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_ASSIGNMENT_STATEMENT_H
#define JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_ASSIGNMENT_STATEMENT_H

#include <jbi/interpreter/abstract_syntax_tree/expression.h>
#include <jbi/interpreter/abstract_syntax_tree/statement.h>

#include <memory>

namespace jbi
{

    class assignment_statement : public statement
    {
    public:
        std::string                 _identifier;
        std::unique_ptr<expression> _initializer;

    public:
        assignment_statement(std::string identifier, std::unique_ptr<expression> initializer) noexcept
            : _identifier(std::move(identifier)), _initializer(std::move(initializer))
        { }

        const std::string& identifier() const noexcept                   { return _identifier; }
        const std::unique_ptr<expression>& initializer() const noexcept  { return _initializer; }
    };

}

#endif
