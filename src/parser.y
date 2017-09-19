%{
#include "syntax.h"

int yylex();
void yyerror(penny_expr** result, const char *s);

%}

%start root

%token LPAREN
%token RPAREN
%token INTEGER
%token SYMBOL
%token STRING

%union {
  penny_expr_value value;
  penny_expr* expr;
}

%type <value.integer> INTEGER "integer"
%type <value.symbol> SYMBOL "symbol"
%type <value.string> STRING "string"
%type <value.list> expr_list "list"
%type <expr> expr "expr"

%parse-param {penny_expr** result}

%%

eof: ;

root: expr eof { *result = $1; }

expr: INTEGER { $$ = penny_expr_integer($1); }
    | SYMBOL { $$ = penny_expr_symbol($1); }
    | STRING { $$ = penny_expr_string($1); }
    | LPAREN expr_list RPAREN { $$ = penny_expr_list($2); }
    ;

expr_list: { $$ = (void*)0; }
         | expr expr_list { $$ = penny_list_cons($2, $1); }
         ;

