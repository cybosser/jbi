#ifndef JBI_INTERPRETER_LEXER_FLEX_SCANNER_H
#define JBI_INTERPRETER_LEXER_FLEX_SCANNER_H

#include <jbi/interpreter/lexer/token.h>

#define YY_DECL jbi::token yylex(yyscan_t);

#include <jbi/interpreter/lexer/flex/scanner_generated.h>

#undef YY_DECL

extern jbi::token yylex(yyscan_t);

#endif
