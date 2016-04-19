#include <jbi/interpreter/lexical_analyser/lexical_analyser.h>

#include <jbi/interpreter/lexical_analyser/flex/scanner.h>

namespace jbi
{

    class lexical_analyser::impl
    {
    private:
        yyscan_t        _scanner;
        YY_BUFFER_STATE _buffer;

    public:
        impl(const std::string& statement)
        {
            JBI_THROW_IF(yylex_init(&_scanner) != 0, std::runtime_error("yylex_init failed!"));

            _buffer = yy_scan_bytes(statement.data(), statement.length(), _scanner);
        }

        ~impl()
        {
            yy_delete_buffer(_buffer, _scanner);

            yylex_destroy(_scanner);
        }

        token read()
        {
            return yylex(_scanner);
        }
    };

    lexical_analyser::lexical_analyser(const std::string& statement)
        : _impl(new impl(statement))
    { }

    lexical_analyser::~lexical_analyser() = default;

    lexical_analyser::lexical_analyser(lexical_analyser&&) noexcept = default;

    lexical_analyser& lexical_analyser::operator=(lexical_analyser&&) noexcept = default;

    token lexical_analyser::read()
    {
        return _impl->read();
    }

}
