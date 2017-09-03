%{
#include "syntax.h"
#include "parser.h"
%}

%%

\( return LPAREN;
\) return RPAREN;
[0-9]+ yylval.value.integer = penny_integer_new(yytext, yyleng); return INTEGER;
[a-zA-Z\-+/*]+ yylval.value.symbol = penny_symbol_new(yytext, yyleng); return SYMBOL;
\"(\\.|[^"])*\" yylval.value.string = penny_string_new(yytext, yyleng); return STRING;
