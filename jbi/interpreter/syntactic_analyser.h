#ifndef JBI_INTERPRETER_SYNTACTIC_ANALYSER_H
#define JBI_INTERPRETER_SYNTACTIC_ANALYSER_H

#include <jbi/interpreter/abstract_syntax_tree/statement.h>
#include <jbi/interpreter/lexical_analyser/lexical_analyser.h>

namespace jbi
{

    class syntactic_analyser
    {
    private:
        lexical_analyser    _tokenizer;

    public:
        explicit syntactic_analyser(lexical_analyser tokenizer)
            : _tokenizer(std::move(tokenizer))
        { }

        std::unique_ptr<statement> parse();
    };
}


#endif
