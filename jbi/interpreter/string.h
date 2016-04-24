#ifndef JBI_INTERPRETER_STRING_H
#define JBI_INTERPRETER_STRING_H

#include <jbi/core/exceptions.h>
#include <jbi/interpreter/exceptions.h>

namespace jbi
{

    namespace detail
    {

        template < typename T >
        struct type_tag
        { };

        inline int from_string(const std::string& str, type_tag<int>)
        {
            return std::stoi(str);
        }

        inline double from_string(const std::string& str, type_tag<double>)
        {
            return std::stod(str);
        }

    }

    template < typename T >
    T from_string(const std::string& str)
    {
        try
        {
            return detail::from_string(str, detail::type_tag<T>());
        }
        catch (const std::invalid_argument& ex)
        {
            JBI_THROW(value_exception(ex.what()));
        }
        catch (const std::out_of_range& ex)
        {
            JBI_THROW(value_exception(ex.what()));
        }
    }

}

#endif
