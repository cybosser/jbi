#include <jbi/interpreter/lexer.h>

namespace jbi
{

    class lexer::impl
    {
    public:
        impl(const std::string& statement)
        { }

        token read_token()
        {
            JBI_THROW(not_implemented_exception());
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