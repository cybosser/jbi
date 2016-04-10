#ifndef JBI_CORE_STRING_H
#define JBI_CORE_STRING_H

#include <sstream>

namespace jbi
{

    template < typename T >
    std::string to_string(const T& value)
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

}

#endif
