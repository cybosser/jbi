#ifndef JBI_VISITOR_ACCEPT_VISITOR_H
#define JBI_VISITOR_ACCEPT_VISITOR_H

#include <jbi/core/exceptions.h>
#include <jbi/core/type_traits.h>
#include <jbi/visitor/visitable.h>

namespace jbi
{

    namespace detail
    {

        template < typename Visitor, typename Visitable >
        return_type_of_decayed<Visitor> accept_visitor(Visitor&&, Visitable&, std::size_t, parameter_pack<>)
        {
            // TODO move into policy
            JBI_THROW(argument_exception("visitable"));
        }

        template < typename Visitor, typename Visitable, typename Head, typename... Tail >
        return_type_of_decayed<Visitor> accept_visitor(Visitor&& visitor, Visitable& visitable, std::size_t tag, parameter_pack<Head, Tail...>)
        {
            if (tag == visitable_tag_holder<Head>::value)
                return std::forward<Visitor>(visitor)(static_cast<Head&>(*static_cast<Head*>(static_cast<void*>(&visitable))));
            return accept_visitor(std::forward<Visitor>(visitor), visitable, tag, parameter_pack<Tail...>());
        }

    }

    // TODO add overloads for const Visitable& and Visitable&&
    template < typename Visitor, typename Visitable >
    return_type_of_decayed<Visitor> accept_visitor(Visitor&& visitor, Visitable& visitable)
    {
        return detail::accept_visitor(std::forward<Visitor>(visitor), visitable, detail::visitable_access::tag(visitable), typename decay_t<Visitor>::acceptable_types());
    };

}

#endif
