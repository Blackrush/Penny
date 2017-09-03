/*
 * penny.c
 * Copyright (C) 2017 antoine <antoine@Antoines-iMac>
 *
 * Distributed under terms of the MIT license.
 */

#include "penny.h"
#include "syntax.h"
#include "stdio.h"

extern int yyparse(penny_expr** result);

int main(int argc, char** argv) {
  penny_expr* expr;
  yyparse(&expr);
  printf("%d\n", expr->type);
  penny_expr_printf(expr);
  printf("\n");
  /* printf("Hello, World!\n"); */
  return 0;
}
