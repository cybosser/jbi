#ifndef JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_NODE_H
#define JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_NODE_H

#include <string>

#include <jbi/visitor/visitable.h>

namespace jbi
{

    class node : public visitable
    {
    public:
        virtual std::string to_string() const = 0;
    };

}

#endif
