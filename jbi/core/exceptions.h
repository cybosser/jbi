#ifndef JBI_CORE_EXCEPTIONS_H
#define JBI_CORE_EXCEPTIONS_H

#include <jbi/core/string.h>
#include <jbi/core/type_traits.h>

#include <stdexcept>

// TODO store context (__FILE__, __LINE__, etc.)
#define JBI_THROW(...) \
    throw __VA_ARGS__

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

    class not_implemented_error : public std::runtime_error
    {
    public:
        not_implemented_error() : std::runtime_error("The method or function is not implemented")
        { }
    };

}

#endif
