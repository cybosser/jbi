#ifndef JBI_CORE_TYPE_TRAITS_H
#define JBI_CORE_TYPE_TRAITS_H

#include <type_traits>

namespace jbi
{

    template < bool B, typename T = void >
    using enable_if_t = typename std::enable_if<B, T>::type;

}

#endif
