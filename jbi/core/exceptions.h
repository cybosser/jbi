#ifndef JBI_CORE_EXCEPTIONS_H
#define JBI_CORE_EXCEPTIONS_H

#include <sstream>
#include <stdexcept>
#include <type_traits>

// TODO store context (__FILE__, __LINE__, etc.)
#define JBI_THROW(...) \
    throw __VA_ARGS__

namespace jbi
{

    // TODO extract context (__FILE__, __LINE__, etc.)
    template < typename T >
    typename std::enable_if<std::is_base_of<std::exception, T>::value, std::string>::type diagnostic_information(const T& exception)
    {
        return exception.what();
    }

    template < typename T >
    typename std::enable_if<!std::is_base_of<std::exception, T>::value, std::string>::type diagnostic_information(const T& value)
    {
        std::ostringstream stream;
        stream << value;
        return stream.str();
    }

    class not_implemented_error : public std::runtime_error
    {
    public:
        not_implemented_error() : std::runtime_error("The method or function is not implemented")
        { }
    };

}

#endif
