#ifndef IJBI_CONSOLE_H
#define IJBI_CONSOLE_H

#include <jbi/interpreter/iterminal.h>

namespace ijbi
{

    class console : public jbi::iterminal
    {
    public:
        virtual std::string read_line() override;
        virtual void write_line(const std::string& line) override;
    };

}

#endif
