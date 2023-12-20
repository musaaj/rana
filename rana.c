#include <stdio.h>
#include "rana.h"
#include "lexer.h"
#include "token_types.h"
#include "expr.h"

char* _getline() {
#define BUFSIZE 2048
  char* buffer = malloc(BUFSIZE);
  char c;
  int i = 0;
  while ((c=getc(stdin)) != '\n') buffer[i++] = c;
  buffer[i] = 0;
  return buffer;
}

int main(int argc, char** argv) {
  token_t** l = malloc(sizeof(token_t) * 40);
  char* input = NULL;
  size_t c = 1024;
  if (argc != 2) {
    printf("Rana v0.0.1\n");
    while (1) {
      printf(">> ");
      input = _getline();
      lexer(input);
      expr_t* expr = parse_expr();
      if (!get_parser_error()) pretty_print(expr);
      printf("\n");
    }
  } else {
    printf("%s run\n", argv[1]);
  }
  free(input);
  return 0;
}
