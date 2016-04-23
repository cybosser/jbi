#ifndef JBI_INTERPRETER_EXCEPTIONS_H
#define JBI_INTERPRETER_EXCEPTIONS_H

#include <stdexcept>

namespace jbi
{

    class syntax_exception : public std::runtime_error
    {
    public:
        explicit syntax_exception(const std::string& message)
            : std::runtime_error("Invalid syntax: " + message)
        { }
    };


    class type_exception : public std::runtime_error
    {
    public:
        explicit type_exception(const std::string& message)
            : std::runtime_error(message)
        { }
    };

}

#endif
