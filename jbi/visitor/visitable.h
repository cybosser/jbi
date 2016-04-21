#ifndef JBI_VISITOR_VISITABLE_H
#define JBI_VISITOR_VISITABLE_H

#include <cstddef>

#define JBI_DEFINE_VISITABLE(Class) \
    private: \
        virtual std::size_t detail_tag() const noexcept override \
        { \
            return jbi::detail::visitable_tag_holder<Class>::value; \
        }

namespace jbi
{

    namespace detail
    {

        struct visitable_tag_generator
        {
            static std::size_t generate()
            {
                static std::size_t generator;
                return ++generator;
            }
        };

        template < typename >
        struct visitable_tag_holder
        {
            static std::size_t value;
        };

        template < typename Visitable >
        std::size_t visitable_tag_holder<Visitable>::value = visitable_tag_generator::generate();

        struct visitable_access;

    }


    class visitable
    {
        friend class detail::visitable_access;

    protected:
        virtual ~visitable() = default;

    private:
        virtual std::size_t detail_tag() const noexcept = 0;
    };


    namespace detail
    {

        struct visitable_access
        {
            static std::size_t tag(const visitable& visitable_)
            {
                return visitable_.detail_tag();
            }
        };

    }

}
#endif
