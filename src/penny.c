/*
 * penny.c
 * Copyright (C) 2017 antoine <antoine@Antoines-iMac>
 *
 * Distributed under terms of the MIT license.
 */

#include "penny.h"
#include "syntax.h"
#include "formatter.h"
#include "parser.h"
#include "stdio.h"

int main(int argc, char** argv) {
  penny_expr* expr;
  yyparse(&expr);
  penny_expr_printf(expr);
  printf("\n");
  penny_expr_free(expr);
  /* printf("Hello, World!\n"); */
  return 0;
}
