#ifndef JBI_INTERPRETER_SYNTAX_TREE_IDENTIFIER_H
#define JBI_INTERPRETER_SYNTAX_TREE_IDENTIFIER_H

#include <jbi/core/exceptions.h>
#include <jbi/interpreter/syntax_tree/expression.h>

#include <string>

namespace jbi
{

    class identifier : public expression
    {
    private:
        std::string _name;

    public:
        explicit identifier(std::string name)
            : _name(std::move(name))
        {
            JBI_THROW_IF(_name.empty(), argument_exception("name"));
        }

        const std::string& name() const noexcept { return _name; }

        JBI_DEFINE_VISITABLE(identifier)
    };
}

#endif
