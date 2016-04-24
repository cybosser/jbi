#ifndef JBI_VALUE_PRINTER_H
#define JBI_VALUE_PRINTER_H

#include <jbi/core/exceptions.h>
#include <jbi/interpreter/iterminal.h>
#include <jbi/interpreter/types/none.h>
#include <jbi/variant/static_visitor.h>

#include <memory>

namespace jbi
{
    namespace detail
    {

        class value_printer : public static_visitor<>
        {
        private:
            std::shared_ptr<iterminal> _terminal;

        public:
            explicit value_printer(std::shared_ptr<iterminal> terminal)
                : _terminal(std::move(terminal))
            {
                JBI_THROW_IF(!_terminal, argument_exception("terminal"));
            }

            template < typename T >
            void operator()(const T& value)
            {
                _terminal->write_line(to_string(value));
            }

            void operator()(none_t)
            { }
        };

    }
}

#endif
