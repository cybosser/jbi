#ifndef JBI_INTERPRETER_LEXER_H
#define JBI_INTERPRETER_LEXER_H

#include <jbi/variant/variant.h>

#include <memory>

namespace jbi
{

    enum operators
    {
        addition,
        subtraction,
        multiplication,
        division
    };


    using token = variant<int, float, operators, std::nullptr_t>; // nullptr_t is an eof indicator


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
