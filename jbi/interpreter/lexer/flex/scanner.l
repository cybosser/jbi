%{
#include <jbi/interpreter/lexer/token.h>
%}

%option never-interactive
%option noyywrap
%option outfile="scanner.cpp" header-file="scanner.h"
%option reentrant
%option extra-type="jbi::token*"

digit   [0-9]
letter  [a-zA-Z]

%%

"="                         { *yyextra = jbi::token::equals(); }

"+"                         { *yyextra = jbi::token::plus(); }
"-"                         { *yyextra = jbi::token::minus(); }
"*"                         { *yyextra = jbi::token::times(); }
"/"                         { *yyextra = jbi::token::slash(); }

{digit}+                    { *yyextra = jbi::token::number(std::atoi(yytext)); }
{digit}+.{digit}*           { *yyextra = jbi::token::number(std::atof(yytext)); }

{letter}({letter}|{digit})* { *yyextra = jbi::token::identifier(yytext); }

[ \t\r\n]                   { }

%%
