#ifndef JBI_ALGORITHM_PP_H
#define JBI_ALGORITHM_PP_H

#include <type_traits>

namespace jbi
{

    // pp stands for 'parameter pack'
    namespace pp
    {

        constexpr std::size_t npos = -1;

        namespace detail
        {

            template < std::size_t Index, typename T, typename... Ts >
            struct index_of_impl;

            template < std::size_t Index, typename T, typename Head, typename... Tail>
            struct index_of_impl<Index, T, Head, Tail...> : std::integral_constant<std::size_t, std::is_same<T, Head>::value? Index : index_of_impl<Index + 1, T, Tail...>::value>
            { };

            template < std::size_t Index, typename T, typename Last >
            struct index_of_impl<Index, T, Last> : std::integral_constant<std::size_t, std::is_same<T, Last>::value? Index : npos>
            { };

        }

        template < typename T, typename... Ts >
        struct index_of : std::integral_constant<std::size_t, detail::index_of_impl<0, T, Ts...>::value>
        { };

    }

}

#endif
