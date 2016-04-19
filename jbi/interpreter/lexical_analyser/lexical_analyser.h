#ifndef JBI_INTERPRETER_LEXICAL_ANALYSER_LEXER_H
#define JBI_INTERPRETER_LEXICAL_ANALYSER_LEXER_H

#include <jbi/interpreter/lexical_analyser/token.h>

namespace jbi
{

    class lexical_analyser
    {
    private:
        // impl hides GNU flex stuff
        class impl;
        std::unique_ptr<impl> _impl;

    public:
        explicit lexical_analyser(const std::string& statement);
        ~lexical_analyser();

        lexical_analyser(lexical_analyser&) = delete;
        lexical_analyser(lexical_analyser&&) noexcept;

        lexical_analyser& operator=(lexical_analyser&) = delete;
        lexical_analyser& operator=(lexical_analyser&&) noexcept;

        token read();
    };

}

#endif
