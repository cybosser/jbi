#ifndef JBI_INTERPRETER_SYNTACTIC_ANALYSER_H
#define JBI_INTERPRETER_SYNTACTIC_ANALYSER_H

#include <jbi/interpreter/lexical_analyser/lexical_analyser.h>
#include <jbi/interpreter/syntax_tree/statement.h>

namespace jbi
{

    class syntactic_analyser
    {
    private:
        class impl;
        std::unique_ptr<impl>   _impl;

    public:
        explicit syntactic_analyser(lexical_analyser tokenizer) noexcept;
        ~syntactic_analyser();

        syntactic_analyser(const syntactic_analyser&) = delete;
        syntactic_analyser(syntactic_analyser&&) noexcept;

        syntactic_analyser& operator=(const syntactic_analyser&) = delete;
        syntactic_analyser& operator=(syntactic_analyser&&) noexcept;

        std::unique_ptr<statement> parse();
    };
}


#endif
