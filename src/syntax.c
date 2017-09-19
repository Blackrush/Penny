/*
 * syntax.c
 * Copyright (C) 2017 antoine <antoine@Antoines-iMac>
 *
 * Distributed under terms of the MIT license.
 */

#include "stdlib.h"
#include "string.h"
#include "syntax.h"

penny_list* penny_list_cons(penny_list* list, penny_expr* value) {
  penny_list* res = (penny_list*) malloc(sizeof(penny_list));
  res->value = value;
  res->next = list;
  return res;
}

penny_integer* penny_integer_new(char* value, int value_len) {
  penny_integer* integer = (penny_integer*) malloc(sizeof(penny_integer));
  integer->value = (char*) calloc(value_len + 1, sizeof(char));
  strncpy(integer->value, value, value_len);
  integer->cached = false;
  integer->cache = 0;
  return integer;
}

penny_symbol* penny_symbol_new(char* value, int value_len) {
  penny_symbol* symbol = (penny_symbol*) malloc(sizeof(penny_symbol));
  symbol->value = (char*) calloc(value_len + 1, sizeof(char));
  strncpy(symbol->value, value, value_len);
  return symbol;
}

penny_string* penny_string_new(char* value, int value_len) {
  penny_string* string = (penny_string*) malloc(sizeof(penny_string));
  string->value = (char*) calloc(value_len + 1, sizeof(char));
  strncpy(string->value, value, value_len);
  return string;
}

penny_expr* penny_expr_list(penny_list* list) {
  penny_expr* expr = (penny_expr*) malloc(sizeof(penny_expr));
  expr->type = PENNY_LIST;
  expr->value.list = list;
  return expr;
}

penny_expr* penny_expr_integer(penny_integer* integer) {
  penny_expr* expr = (penny_expr*) malloc(sizeof(penny_expr));
  expr->type = PENNY_INTEGER;
  expr->value.integer = integer;
  return expr;
}

penny_expr* penny_expr_symbol(penny_symbol* symbol) {
  penny_expr* expr = (penny_expr*) malloc(sizeof(penny_expr));
  expr->type = PENNY_SYMBOL;
  expr->value.symbol = symbol;
  return expr;
}

penny_expr* penny_expr_string(penny_string* string) {
  penny_expr* expr = (penny_expr*) malloc(sizeof(penny_expr));
  expr->type = PENNY_STRING;
  expr->value.string = string;
  return expr;
}

void penny_list_free(penny_list* list) {
  if (list->next != NULL) {
    penny_list_free(list->next);
  }
  penny_expr_free(list->value);
  free(list);
}

void penny_integer_free(penny_integer* integer) {
  free(integer->value);
  free(integer);
}

void penny_symbol_free(penny_symbol* symbol) {
  free(symbol->value);
  free(symbol);
}

void penny_string_free(penny_string* string) {
  free(string->value);
  free(string);
}

void penny_expr_free(penny_expr* expr) {
  switch (expr->type) {
    case PENNY_LIST:
      penny_list_free(expr->value.list);
      break;

    case PENNY_INTEGER:
      penny_integer_free(expr->value.integer);
      break;

    case PENNY_SYMBOL:
      penny_symbol_free(expr->value.symbol);
      break;

    case PENNY_STRING:
      penny_string_free(expr->value.string);
      break;
  }
  free(expr);
}
