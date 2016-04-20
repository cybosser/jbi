#ifndef JBI_CORE_STRING_H
#define JBI_CORE_STRING_H

#include <jbi/core/type_traits.h>

#include <sstream>

namespace jbi
{

    namespace detail
    {

        template < typename T >
        class has_to_string_method_impl
        {
        private:
            template < typename U >
            static constexpr auto test(U*) -> is_convertible_t<decltype(std::declval<U>().to_string()), std::string>;

            template < typename >
            static constexpr std::false_type test(...);

        public:
            using type = decltype(test<T>(nullptr));
        };

        template < typename T >
        class has_to_string_method : public has_to_string_method_impl<T>::type
        { };

    }

    template < typename T >
    enable_if_t<!detail::has_to_string_method<T>::value, std::string> to_string(const T& value)
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }

    template < typename T >
    enable_if_t<detail::has_to_string_method<T>::value, std::string> to_string(const T& value)
    {
        return value.to_string();
    }

}

#endif
