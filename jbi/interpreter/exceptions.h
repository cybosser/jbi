#ifndef JBI_INTERPRETER_EXCEPTIONS_H
#define JBI_INTERPRETER_EXCEPTIONS_H

#include <stdexcept>

namespace jbi
{

    class interpreter_exception : public std::runtime_error
    {
    public:
        interpreter_exception(const std::string& message)
            : std::runtime_error(message)
        { }
    };


    class arithmetic_exception : public interpreter_exception
    {
    public:
        explicit arithmetic_exception(const std::string& message)
            : interpreter_exception(message)
        { }
    };


    class name_exception : public interpreter_exception
    {
    public:
        explicit name_exception(const std::string& message)
            : interpreter_exception(message)
        { }
    };


    class syntax_exception : public interpreter_exception
    {
    public:
        explicit syntax_exception(const std::string& message)
            : interpreter_exception("Invalid syntax: " + message)
        { }
    };


    class type_exception : public interpreter_exception
    {
    public:
        explicit type_exception(const std::string& message)
            : interpreter_exception(message)
        { }
    };


    class value_exception : public interpreter_exception
    {
    public:
        explicit value_exception(const std::string& message)
            : interpreter_exception(message)
        { }
    };

}

#endif
