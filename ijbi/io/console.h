#ifndef IJBI_IO_CONSOLE_H
#define IJBI_IO_CONSOLE_H

#include <string>

namespace ijbi
{

    class console
    {
    public:
        std::string read_line();
        void write_line(const std::string& line);
    };

}

#endif
