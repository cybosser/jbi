#ifndef JBI_INTERPRETER_TYPES_VALUE_H
#define JBI_INTERPRETER_TYPES_VALUE_H

#include <jbi/variant/variant.h>
#include <jbi/interpreter/types/numeric_range.h>

namespace jbi
{

    using value = variant<int, double, numeric_range<int>>;

}

#endif
