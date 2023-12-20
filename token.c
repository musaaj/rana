#include "token_types.h"

token_t* new_token(int type, int line, int column, char* value) {
  token_t* token = malloc(sizeof(token_t));
  token->type = type;
  token->line = line;
  token->column = column;
  token->value = value;
  return token;
}

void print_token(token_t* token) {
  if (!token) {
    puts("Token: Nil");
    return;
  }
  puts("Token: {");
  printf("  type: %d\n", token->type);
  printf("  line: %d\n", token->line);
  printf("  column: %d\n", token->column);
  printf("  value: %s\n", token->value);
  puts("}");
}
