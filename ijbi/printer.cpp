#include <ijbi/printer.h>

#include <jbi/core/exceptions.h>

namespace ijbi
{

    printer::printer(std::shared_ptr<console> console)
        : _console(std::move(console))
    {
        JBI_THROW_IF(!_console, jbi::argument_exception("console"));
    }

    void printer::operator()(const jbi::none_t&)
    { }

}
