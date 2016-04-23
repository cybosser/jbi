#include <jbi/interpreter/types/none.h>

namespace jbi
{

    const none_t none;

    bool operator==(const none_t&, const none_t&) noexcept
    {
        return true;
    }

    bool operator!=(const none_t& left, const none_t& right) noexcept
    {
        return !(left == right);
    }

}