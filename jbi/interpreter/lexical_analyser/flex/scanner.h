#ifndef JBI_INTERPRETER_LEXICAL_ANALYSER_FLEX_SCANNER_H
#define JBI_INTERPRETER_LEXICAL_ANALYSER_FLEX_SCANNER_H

#include <jbi/interpreter/lexical_analyser/token.h>

#define YY_DECL jbi::token yylex(yyscan_t);

#include <jbi/interpreter/lexical_analyser/flex/scanner_generated.h>

#undef YY_DECL

extern jbi::token yylex(yyscan_t);

#endif
