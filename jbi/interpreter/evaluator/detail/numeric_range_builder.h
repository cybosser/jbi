#ifndef JBI_INTERPRETER_EVALUATOR_DETAIL_NUMERIC_RANGE_BUILDER_H
#define JBI_INTERPRETER_EVALUATOR_DETAIL_NUMERIC_RANGE_BUILDER_H

#include <jbi/interpreter/exceptions.h>
#include <jbi/interpreter/types/numeric_range.h>
#include <jbi/variant/static_visitor.h>

namespace jbi
{
    namespace detail
    {

        class numeric_range_builder : public static_visitor<numeric_range<int>>
        {
        public:
            numeric_range<int> operator()(int start, int stop) const
            {
                JBI_THROW_UNLESS(start < stop, value_exception("Invalid range end"));
                return numeric_range<int>(start, stop);
            }

            template < typename T, typename U >
            numeric_range<int> operator()(const T&, const U&) const
            {
                JBI_THROW(type_exception("Invalid type of range begin/end"));
            };
        };

    }
}
#endif
