#include "lexer.h"
#include "token_types.h"
#include "expr.h"

static bool parser_error = false;
bool get_parser_error(){ return parser_error;}

expr_t* parse_expr(int prec) {
  expr_t* expr = parse_term();
  while (!eof() && prec < get_prec(peek())) {
    token_t* token = next();
    int new_prec = get_prec(token);
    expr = new_expr(expr, token, parse_expr(new_prec)); 
  }
  return expr;
}

expr_t* parse_term() {
  int types[3] = {NUMBER, STRING, IDENTIFIER};
  if (match(types, 3))
  {
    expr_t* expr = new_expr(NULL, next(), NULL);
    return expr;
  } else if (check(LEFT_PAREN)) {
    next();
    expr_t* expr = parse_expr(0);
    next();
    return expr;
  }
  puts("Error: syntax error");
  return NULL;
}

bool check(int type) {
  token_t* current = peek();
  if (!current) return false;
  if (current->type == type) return true;
  return false;
}

bool match(int* types, int count) {
  for (int i = 0; i < count; i++) {
    if (check(types[i])) return true;
  }
  return false;
}

expr_t* new_expr(expr_t* left, token_t* value, expr_t* right) {
  expr_t* expr = malloc(sizeof(expr_t));
  expr->value = value;
  expr->left = left;
  expr->right = right;
  return expr;
}

int get_prec(token_t* token) {
  if (!token) return 0;
  switch (token->type) {
    case EQUAL: return 10;
    case PLUS:
    case MINUS: return 30;
    case DIV:
    case MUL:
    case MOD: return 31;
    default: return 0;
  }
}

void pretty_print(expr_t* expr) {
  if (expr && expr->left && expr->right) {
    printf("(%s ", expr->value->value);
    pretty_print(expr->left);
    printf(" ");
    pretty_print(expr->right);
    printf(")");
  } else if (expr){
    printf("%s", expr->value->value);
  }
}
