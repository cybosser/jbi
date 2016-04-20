#include <ijbi/console.h>

#include <jbi/core/exceptions.h>
#include <jbi/interpreter/interpreter.h>

#include <ijbi/printer.h>

void run(ijbi::console& console)
{
    ijbi::printer printer(console);

    jbi::interpreter interpreter;

    while (true)
    {
        const std::string statement = console.read_line();
        if (statement == "exit")
            return;

        try
        {
            const jbi::value result = interpreter.interpret(statement);
            jbi::apply_visitor(result, printer);
        }
        catch (const jbi::syntax_exception& ex)
        {
            console.write_line(ex.what());
        }
    }
}

int main()
{
    ijbi::console console;

    console.write_line("Welcome to ijbi, an interactive interpreter");
    console.write_line("Type 'exit' to exit");

    try
    {
        run(console);
    }
    catch (const std::exception& ex)
    {
        console.write_line(jbi::diagnostic_information(ex));

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
