#ifndef JBI_ALGORITHM_PP_H
#define JBI_ALGORITHM_PP_H

#include <jbi/core/type_traits.h>

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
            struct index_of_impl<Index, T, Head, Tail...> : conditional_t<std::is_same<T, Head>::value, size_t_constant<Index>, index_of_impl<Index + 1, T, Tail...>>
            { };

            template < std::size_t Index, typename T, typename Last >
            struct index_of_impl<Index, T, Last> : conditional_t<std::is_same<T, Last>::value, size_t_constant<Index>, size_t_constant<npos>>
            { };

        }

        template < typename T, typename... Ts >
        using index_of = detail::index_of_impl<0, T, Ts...>;

        namespace detail
        {

            template < typename Head, typename... >
            struct front_impl
            {
                using type = Head;
            };

            template < typename... Ts >
            struct back_impl;

            template < typename Head, typename... Tail >
            struct back_impl<Head, Tail...> : public detail::back_impl<Tail...>
            { };

            template < typename Last >
            struct back_impl<Last>
            {
                using type = Last;
            };

        }

        template < typename... Ts >
        using front = typename detail::front_impl<Ts...>::type;

        template < typename... Ts >
        using back = typename detail::back_impl<Ts...>::type;

    }

}

#endif
