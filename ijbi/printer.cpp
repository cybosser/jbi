#include <ijbi/printer.h>

namespace ijbi
{

    printer::printer(console console)
        : _console(std::move(console))
    { }

}