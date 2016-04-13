#ifndef IJBI_PRINTER_H
#define IJBI_PRINTER_H

#include <ijbi/console.h>

#include <jbi/core/static_visitor.h>
#include <jbi/core/string.h>

namespace ijbi
{

    class printer : public jbi::static_visitor<>
    {
    private:
        console _console;

    public:
        explicit printer(console console);

        template < typename T >
        void operator()(const T& value)
        {
            _console.write_line(jbi::to_string(value));
        }
    };

}

#endif
