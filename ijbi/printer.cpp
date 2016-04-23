#include <ijbi/printer.h>

namespace ijbi
{

    printer::printer(console console) noexcept
        : _console(std::move(console))
    { }

    void printer::operator()(const jbi::none_t&)
    { }

}
