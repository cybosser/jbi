%{
#include <jbi/interpreter/lexical_analyser/token.h>

#define YY_DECL jbi::token yylex(yyscan_t yyscanner)

#define yyterminate() return jbi::token::eof()
%}

%option never-interactive
%option noyywrap
%option outfile="scanner.cpp" header-file="scanner_generated.h"
%option reentrant

digit   [0-9]
letter  [a-zA-Z]

%%

"var"                       { return jbi::token::var(); }
"in"                        { return jbi::token::in(); }
"out"                       { return jbi::token::out(); }
"print"                     { return jbi::token::print(); }

{digit}+\.{digit}*          { return jbi::token::literal(std::atof(yytext)); }
{digit}+                    { return jbi::token::literal(std::atoi(yytext)); }
\"(\\.|[^\\"])*\"           { return jbi::token::literal(yytext); }

{letter}({letter}|{digit})* { return jbi::token::identifier(yytext); }

"->"                        { return jbi::token::arrow(); }

"="                         { return jbi::token::equals(); }
"+"                         { return jbi::token::plus(); }
"-"                         { return jbi::token::minus(); }
"*"                         { return jbi::token::asterisk(); }
"/"                         { return jbi::token::slash(); }
"^"                         { return jbi::token::carret(); }
","                         { return jbi::token::comma(); }
"("                         { return jbi::token::left_parenthesis(); }
")"                         { return jbi::token::right_parenthesis(); }
"{"                         { return jbi::token::left_brace(); }
"}"                         { return jbi::token::right_brace(); }

[ \t\r\n]                   { }

.                           { JBI_THROW(jbi::syntax_exception(std::string("unexpected token ")+ yytext)); }

%%
