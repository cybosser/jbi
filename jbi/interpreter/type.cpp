#include <jbi/interpreter/type.h>

namespace jbi
{

    type type::common_type(const type& first, const type& second)
    {
        if (first == type::int_() && second == type::int_())
            return type::int_();

        return type::double_();
    }

}