#ifndef JBI_CORE_VARIANT_H
#define JBI_CORE_VARIANT_H

#include <jbi/algorithm/pp.h>
#include <jbi/core/exceptions.h>
#include <jbi/core/static_visitor.h>
#include <jbi/core/type_traits.h>

#include <memory>
#include <typeinfo>

namespace jbi
{

    namespace detail
    {

        template < typename... Ts >
        struct variant_storage
        {
        private:
            aligned_union_t<0, Ts...>   _storage;

        public:
            void* address()
            {
                return std::addressof(_storage);
            }

            const void* address() const
            {
                return std::addressof(_storage);
            }
        };


        template < typename T >
        using return_type_t = typename T::return_type;


        template < typename... Ts >
        class parameter_pack
        {
        public:
            template < typename Op >
            return_type_t<Op> apply_for(Op op, std::size_t index)
            {
                return apply_for_impl<Op, Ts...>(op, index);
            };

        private:
            template < typename Op, typename Head, typename... Tail >
            return_type_t<Op> apply_for_impl(Op op, std::size_t index)
            {
                if (index == 0)
                    return op.template apply<Head>();

                return apply_for_impl<Op, Tail...>(op, index - 1);
            }

            template < typename Op >
            return_type_t<Op> apply_for_impl(Op, std::size_t)
            {
                JBI_THROW(std::logic_error("Should never get here"));
            }
        };


        template < typename Visitor, typename Address >
        class visitor_applier
        {
        private:
            Visitor&    _visitor;
            Address     _address;

        public:
            using return_type = return_type_t<Visitor>;

            visitor_applier(Visitor& visitor, Address address)
                : _visitor(visitor), _address(address)
            { }

            template < typename T >
            return_type apply()
            {
                return _visitor(to_reference<T>(_address));
            }

        private:
            template < typename T >
            T& to_reference(void* address)
            {
                return static_cast<T&>(*static_cast<T*>(address));
            }

            template < typename T >
            const T& to_reference(const void* address)
            {
                return static_cast<const T&>(*static_cast<const T*>(address));
            }
        };

        template < typename Visitor, typename ParameterPack, typename Address >
        return_type_t<Visitor> apply_visitor(Visitor& visitor, Address address, ParameterPack pack, std::size_t which)
        {
            visitor_applier<Visitor, Address> applier(visitor, address);
            return pack.apply_for(applier, which);
        }


        class variant_copier : public static_visitor<>
        {
        private:
            void* _address;

        public:
            explicit variant_copier(void* address)
                : _address(address)
            { }

            template < typename T >
            void operator()(T& value)
            {
                new(_address) T(value);
            }
        };


        class variant_mover : public static_visitor<>
        {
        private:
            void* _address;

        public:
            explicit variant_mover(void* address)
                : _address(address)
            { }

            template < typename T >
            void operator()(T& value)
            {
                new(_address) T(std::move(value));
            }
        };


        struct variant_destroyer : public static_visitor<>
        {
            template < typename T >
            void operator()(T& value)
            {
                value.~T();
            }
        };

    }


    template < typename... Ts >
    class variant
    {
    private:
        std::size_t                     _which;
        detail::variant_storage<Ts...>  _storage;

    public:
        template < typename T, enable_if_t<!std::is_same<decay_t<T>, variant>::value, void>* = nullptr >
        explicit variant(T&& value)
            : _which(pp::index_of<decay_t<T>, Ts...>::value)
        {
            using decayed_t = decay_t<T>;

            // TODO check convertibility instead of exact type
            static_assert(pp::index_of<decayed_t, Ts...>::value != pp::npos, "T should be one of the Ts");
            new(_storage.address()) decayed_t(std::forward<T>(value));
        }

        variant(const variant& other)
        {
            detail::variant_copier copier(_storage.address());
            other.apply_visitor(copier);

            _which = other._which;
        }

        variant(variant&& other)
        {
            detail::variant_mover mover(_storage.address());
            other.apply_visitor(mover);

            _which = other._which;
        }

        ~variant()
        {
            detail::variant_destroyer destroyer;
            apply_visitor(destroyer);
        }

        variant& operator=(const variant&) = delete;
        variant& operator=(variant&&) = delete;

        template < typename Visitor >
        detail::return_type_t<Visitor> apply_visitor(Visitor& visitor)
        {
            return detail::apply_visitor(visitor, _storage.address(), detail::parameter_pack<Ts...>(), _which);
        }

        template < typename Visitor >
        detail::return_type_t<Visitor> apply_visitor(Visitor& visitor) const
        {
            return detail::apply_visitor(visitor, _storage.address(), detail::parameter_pack<Ts...>(), _which);
        }
    };


    // TODO add descriptive message
    class bad_get : public std::bad_cast
    { };


    namespace detail
    {

        template < typename T >
        struct variant_getter : public static_visitor<T&>
        {
            T& operator()(T& value)
            {
                return value;
            }

            template < typename U >
            T& operator()(U&)
            {
                JBI_THROW(bad_get());
            }
        };

    }

    template < typename T, typename... Ts >
    T& get(variant<Ts...>& variant)
    {
        detail::variant_getter<T> getter;
        return variant.apply_visitor(getter);
    }

    template < typename T, typename... Ts >
    const T& get(const variant<Ts...>& variant)
    {
        detail::variant_getter<const T> getter;
        return variant.apply_visitor(getter);
    }


    template < typename... Ts, typename Visitor >
    detail::return_type_t<Visitor> apply_visitor(variant<Ts...>& variant, Visitor& visitor)
    {
        return variant.apply_visitor(visitor);
    };

    template < typename... Ts, typename Visitor >
    detail::return_type_t<Visitor> apply_visitor(const variant<Ts...>& variant, Visitor& visitor)
    {
        return variant.apply_visitor(visitor);
    };

}

#endif
