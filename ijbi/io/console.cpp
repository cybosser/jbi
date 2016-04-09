#include <ijbi/io/console.h>

#include <iostream>

namespace ijbi
{

    std::string console::read_line()
    {
        std::string line;
        std::getline(std::cin, line);
        return line;
    }

    void console::write_line(const std::string &line)
    {
        std::cout << line << std::endl;
    }

}
