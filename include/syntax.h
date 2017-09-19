/*
 * syntax.h
 * Copyright (C) 2017 antoine <antoine@Antoines-iMac>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef SYNTAX_H
#define SYNTAX_H

#include <stdbool.h>

struct penny_expr;
typedef struct penny_expr penny_expr;

typedef struct __penny_list {
  penny_expr* value;
  struct __penny_list* next;
} penny_list;

penny_list* penny_list_cons(penny_list* list, penny_expr* value);

typedef struct {
  char* value;
  bool cached;
  long long cache;
} penny_integer;

penny_integer* penny_integer_new(char* value, int value_len);

typedef struct {
  char* value;
} penny_symbol;

penny_symbol* penny_symbol_new(char* value, int value_len);

typedef struct {
  char* value;
} penny_string;

penny_string* penny_string_new(char* value, int value_len);

typedef enum {
  PENNY_LIST,
  PENNY_INTEGER,
  PENNY_SYMBOL,
  PENNY_STRING,
} penny_expr_type;

typedef union {
  penny_list* list;
  penny_integer* integer;
  penny_symbol* symbol;
  penny_string* string;
} penny_expr_value;

struct penny_expr {
  penny_expr_type type;
  penny_expr_value value;
};

penny_expr* penny_expr_list(penny_list* list);
penny_expr* penny_expr_integer(penny_integer* integer);
penny_expr* penny_expr_symbol(penny_symbol* symbol);
penny_expr* penny_expr_string(penny_string* string);
void penny_expr_free(penny_expr* expr);

#endif /* !SYNTAX_H */
