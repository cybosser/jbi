#include <ijbi/io/console.h>

#include <jbi/interpreter/interpreter.h>

#include <cstdlib>

int main()
{
    ijbi::console console;

    console.write_line("Welcome to ijbi, an interactive interpreter");
    console.write_line("Type 'exit' to exit");

    jbi::interpreter interpreter;

    try
    {
        while (true)
        {
            const std::string statement = console.read_line();
            if (statement == "exit")
                return EXIT_SUCCESS;

            interpreter.interpret(statement);
        }
    }
    catch (const std::exception& ex)
    {
        // TODO output diagnostic information
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
