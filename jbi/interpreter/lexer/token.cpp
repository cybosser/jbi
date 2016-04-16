#include <jbi/interpreter/lexer/token.h>

namespace jbi
{

    bool operator==(const token& left, const token& right)
    {
        return left.tag() == right.tag() && left.value() == right.value();
    }

    bool operator!=(const token& left, const token& right)
    {
        return !(left == right);
    }

}
