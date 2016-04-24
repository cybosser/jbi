#ifndef JBI_INTERPRETER_ITERMINAL_H
#define JBI_INTERPRETER_ITERMINAL_H

#include <string>

namespace jbi
{

    struct iterminal
    {
        virtual ~iterminal() = default;

        virtual std::string read_line() = 0;
        virtual void write_line(const std::string& line) = 0;
    };

}

#endif
