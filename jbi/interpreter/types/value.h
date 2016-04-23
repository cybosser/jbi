#ifndef JBI_INTERPRETER_TYPES_VALUE_H
#define JBI_INTERPRETER_TYPES_VALUE_H

#include <jbi/variant/variant.h>
#include <jbi/interpreter/types/none.h>

namespace jbi
{

    using value = variant<none_t, int, double>;

}

#endif
