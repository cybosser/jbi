#ifndef JBI_CORE_TYPE_TRAITS_H
#define JBI_CORE_TYPE_TRAITS_H

#include <type_traits>

namespace jbi
{

    template < std::size_t Length, typename... Ts >
    using aligned_union_t = typename std::aligned_union<Length, Ts...>::type;

    template < bool Condition, typename T, typename F >
    using conditional_t = typename std::conditional<Condition, T, F>::type;

    template < bool Condition, typename T = void >
    using enable_if_t = typename std::enable_if<Condition, T>::type;

}

#endif
