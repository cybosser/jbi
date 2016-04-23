#ifndef IJBI_PRINTER_H
#define IJBI_PRINTER_H

#include <ijbi/console.h>

#include <jbi/core/string.h>
#include <jbi/interpreter/types/none.h>
#include <jbi/variant/static_visitor.h>

namespace ijbi
{

    class printer : public jbi::static_visitor<>
    {
    private:
        console _console;

    public:
        explicit printer(console console) noexcept;

        void operator()(const jbi::none_t&);

        template < typename T >
        void operator()(const T& value)
        {
            _console.write_line(jbi::to_string(value));
        }
    };

}

#endif
