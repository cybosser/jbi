#ifndef JBI_CORE_EXCEPTIONS_H
#define JBI_CORE_EXCEPTIONS_H

#include <stdexcept>

// TODO store context (__FILE__, __LINE__, etc.)
#define JBI_THROW(...) \
    throw __VA_ARGS__

namespace jbi
{

    class not_implemented_error : public std::runtime_error
    {
    public:
        not_implemented_error() : std::runtime_error("The method or function is not implemented")
        { }
    };

}

#endif
