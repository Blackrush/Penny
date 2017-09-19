#ifndef FORMAT_H
#define FORMAT_H

#include "syntax.h"

void penny_list_printf(penny_list* list);
void penny_integer_printf(penny_integer* integer);
void penny_symbol_printf(penny_symbol* symbol);
void penny_string_printf(penny_string* string);
void penny_expr_printf(penny_expr* expr);

#endif//FORMAT_H