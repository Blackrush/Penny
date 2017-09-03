/*
 * syntax.c
 * Copyright (C) 2017 antoine <antoine@Antoines-iMac>
 *
 * Distributed under terms of the MIT license.
 */

#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "syntax.h"

penny_list_node* penny_list_node_new(penny_expr* value) {
  penny_list_node* node = (penny_list_node*) malloc(sizeof(penny_list_node));
  node->value = value;
  node->next = NULL;
  node->previous = NULL; 
  return node;
}

void penny_list_node_link(penny_list_node* left, penny_list_node* right) {
  if (left != NULL) {
    left->next = right;
  }
  if (right != NULL) {
    right->previous = left;
  }
}

penny_list* penny_list_new(void) {
  penny_list* list = (penny_list*) malloc(sizeof(penny_list));
  list->len = 0;
  list->hd = NULL;
  return list;
}

void penny_list_cons(penny_list* list, penny_expr* value) {
  list->len++;
  penny_list_node* hd = penny_list_node_new(value);
  penny_list_node* old_hd = list->hd;
  penny_list_node_link(hd, old_hd);
  list->hd = hd;
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

void penny_list_printf(penny_list* list) {
  int i;
  penny_list_node* x = list->hd;

  printf("(");
  for (i = 0; i < list->len; i++) {
    penny_expr_printf(x->value);

    if (x->next != NULL) {
      printf(" ");
    }
    x = x->next;
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

void penny_list_free(penny_list* list) {
  int i;
  penny_list_node* x = list->hd;

  for (i = 0; i < list->len; i++) {
    penny_expr_free(x->value);
    x = x->next;
  }
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
