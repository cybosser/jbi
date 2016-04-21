#ifndef JBI_VISITOR_VISITOR_H
#define JBI_VISITOR_VISITOR_H

#include <jbi/core/type_traits.h>

namespace jbi
{

    template < typename ReturnType, typename... AcceptableTypes >
    struct visitor
    {
        using return_type = ReturnType;
        using acceptable_types = parameter_pack<AcceptableTypes...>;
    };

}

#endif
