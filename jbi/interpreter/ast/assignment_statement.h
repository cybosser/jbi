#ifndef JBI_INTERPRETER_AST_ASSIGNMENT_STATEMENT_H
#define JBI_INTERPRETER_AST_ASSIGNMENT_STATEMENT_H

#include <jbi/interpreter/ast/expression.h>
#include <jbi/interpreter/ast/statement.h>

#include <memory>

namespace jbi
{

    class assignment_statement : public statement
    {
    public:
        std::string                 _identifier;
        std::unique_ptr<expression> _initializer;
    public:
        assignment_statement(std::string identifier, std::unique_ptr<expression> initializer)
            : _identifier(std::move(identifier)), _initializer(std::move(initializer))
        { }

        const std::string& identifier() const                   { return _identifier; }
        const std::unique_ptr<expression>& initializer() const  { return _initializer; }
    };

}

#endif
