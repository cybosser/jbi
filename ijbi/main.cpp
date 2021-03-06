#include <ijbi/console.h>

#include <jbi/interpreter/exceptions.h>
#include <jbi/interpreter/interpreter.h>

void run(const std::shared_ptr<ijbi::console>& console)
{
    JBI_THROW_IF(!console, jbi::argument_exception("console"));

    jbi::interpreter interpreter(console);

    while (true)
    {
        const std::string statement = console->read_line();
        if (statement == "exit")
            return;

        try
        {
            interpreter.interpret(statement);
        }
        catch (const jbi::interpreter_exception& ex)
        {
            console->write_line(ex.what());
        }
    }
}

int main()
{
    std::shared_ptr<ijbi::console> console = std::make_shared<ijbi::console>();

    console->write_line("Welcome to ijbi, an interactive interpreter");
    console->write_line("Type 'exit' to exit");

    try
    {
        run(console);
    }
    catch (const std::exception& ex)
    {
        console->write_line(jbi::diagnostic_information(ex));

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
