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

    template < typename From, typename To >
    using is_convertible_t = typename std::is_convertible<From, To>::type;

    template < std::size_t Value >
    using size_t_constant = std::integral_constant<std::size_t, Value>;

    template < typename T >
    using return_type_of = typename T::return_type;

    template < typename T >
    using return_type_of_decayed = return_type_of<decay_t<T>>;

    template < typename... Ts >
    struct parameter_pack
    { };

}

#endif
