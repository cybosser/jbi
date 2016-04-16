#ifndef JBI_INTERPRETER_LEXER_LEXER_H
#define JBI_INTERPRETER_LEXER_LEXER_H

#include <jbi/interpreter/lexer/token.h>

namespace jbi
{

    class lexer
    {
    private:
        // impl hides GNU flex stuff
        class impl;
        std::unique_ptr<impl> _impl;

    public:
        explicit lexer(const std::string& statement);
        ~lexer();

        token read_token();
    };

}

#endif
