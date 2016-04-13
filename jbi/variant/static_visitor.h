#ifndef JBI_VARIANT_STATIC_VISITOR_H
#define JBI_VARIANT_STATIC_VISITOR_H

namespace jbi
{

    template < typename ReturnType = void >
    struct static_visitor
    {
        using return_type = ReturnType;
    };

}

#endif
