#ifndef JBI_CORE_EXCEPTIONS_H
#define JBI_CORE_EXCEPTIONS_H

#include <jbi/core/string.h>
#include <jbi/core/type_traits.h>

#include <stdexcept>

// TODO store context (__FILE__, __LINE__, etc.)
#define JBI_THROW(Exception) \
    throw Exception

#define JBI_THROW_IF(Condition, Exception) \
    do \
    { \
        if (Condition) \
            JBI_THROW(Exception); \
    } \
    while (false)

#define JBI_THROW_UNLESS(Condition, Exception) \
    JBI_THROW_IF(!(Condition), Exception)

namespace jbi
{

    // TODO extract context (__FILE__, __LINE__, etc.)
    template < typename T >
    enable_if_t<std::is_base_of<std::exception, T>::value, std::string> diagnostic_information(const T& ex)
    {
        return ex.what();
    }

    template < typename T >
    enable_if_t<!std::is_base_of<std::exception, T>::value, std::string> diagnostic_information(const T& value)
    {
        return to_string(value);
    }


    class invalid_operation_exception : public std::runtime_error
    {
    public:
        explicit invalid_operation_exception(const std::string& message)
            : std::runtime_error(message)
        { }
    };


    class not_implemented_exception : public std::runtime_error
    {
    public:
        not_implemented_exception()
            : std::runtime_error("The method or function is not implemented")
        { }
    };


    class argument_exception : public std::invalid_argument
    {
    public:
        explicit argument_exception(const std::string& name)
            : std::invalid_argument("Invalid argument: " + name)
        { }
    };

}

#endif
