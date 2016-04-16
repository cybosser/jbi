#include <jbi/interpreter/lexer/lexer.h>

#include <jbi/interpreter/lexer/flex/scanner.h>

namespace jbi
{

    class lexer::impl
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

        token read_token()
        {
            return yylex(_scanner);
        }
    };

    lexer::lexer(const std::string& statement)
        : _impl(new impl(statement))
    { }

    lexer::~lexer()
    { }

    token lexer::read_token()
    {
        return _impl->read_token();
    }

}