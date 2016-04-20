#ifndef JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_NODE_H
#define JBI_INTERPRETER_ABSTRACT_SYNTAX_TREE_NODE_H

#include <string>

namespace jbi
{

    struct node
    {
        virtual ~node() = default;

        virtual std::string to_string() const = 0;
    };

}

#endif
