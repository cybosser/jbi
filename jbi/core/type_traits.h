#ifndef JBI_CORE_TYPE_TRAITS_H
#define JBI_CORE_TYPE_TRAITS_H

#include <type_traits>

namespace jbi
{

    template < std::size_t Length, typename... Ts >
    using aligned_union_t = typename std::aligned_union<Length, Ts...>::type;

    template < bool Condition, typename T, typename F >
    using conditional_t = typename std::conditional<Condition, T, F>::type;

    template < typename T >
    using decay_t = typename std::decay<T>::type;

    template < bool Condition, typename T = void >
    using enable_if_t = typename std::enable_if<Condition, T>::type;

    template < std::size_t Value >
    using size_t_constant = std::integral_constant<std::size_t, Value>;

}

#endif
