#include "formatter.h"
#include "stdio.h"

void penny_list_printf(penny_list* list) {
  penny_list* it;

  printf("(");
  for (it = list; it != NULL; it = it->next) {
    if (it != list) {
      printf(" ");
    }
    penny_expr_printf(it->value);
  }
  printf(")");
}

void penny_integer_printf(penny_integer* integer) {
  printf("%s", integer->value);
}

void penny_symbol_printf(penny_symbol* symbol) {
  printf("%s", symbol->value);
}

void penny_string_printf(penny_string* string) {
  printf("%s", string->value);
}

void penny_expr_printf(penny_expr* expr) {
  switch (expr->type) {
    case PENNY_LIST:
      penny_list_printf(expr->value.list);
      break;

    case PENNY_INTEGER:
      penny_integer_printf(expr->value.integer);
      break;

    case PENNY_SYMBOL:
      penny_symbol_printf(expr->value.symbol);
      break;

    case PENNY_STRING:
      penny_string_printf(expr->value.string);
      break;
  }
}