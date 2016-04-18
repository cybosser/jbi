#ifndef JBI_CORE_UTILITY_H
#define JBI_CORE_UTILITY_H

namespace jbi
{

    template < typename T, typename... Ts >
    bool is_one_of(const T& actual, const T& expected)
    {
        return actual == expected;
    };

    template < typename T, typename... Ts >
    bool is_one_of(const T& actual, const T& expected, const Ts&... tail)
    {
        return actual == expected || is_one_of(actual, tail...);
    };

}

#endif
