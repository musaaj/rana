#ifndef PARSER_H
#define PARSER_H
#include "rana.h"
#include "token_types.h"

typedef struct expression_s {
  token_t* value;
  struct expression_s* left;
  struct expression_s* right;
} expr_t;

expr_t* new_expr(expr_t* left, token_t* value, expr_t* right);
expr_t* parse_expr(int);
expr_t* parse_term();
bool get_parser_error();
int get_prec(token_t* token);
bool match(int* types, int count);
bool check(int type);
void pretty_print(expr_t* expr); 
#endif
