#include <jbi/interpreter/interpreter.h>

#include <cstdlib>

int main()
{
    try
    {
        jbi::interpreter interpreter;
        interpreter.interpret("2+2");
    }
    catch (const std::exception& ex)
    {
        // TODO output diagnostic information
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
