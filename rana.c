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
  char* input = NULL;
  if (argc != 2) {
    printf("Rana v0.0.1\n");
    while (1) {
      printf(">> ");
      input = _getline();
      lexer(input);
      expr_t* expr = parse_expr(0);
      if (!get_parser_error()) pretty_print(expr);
      printf("\n");
      free(expr);
    }
  } else {
    printf("%s run\n", argv[1]);
  }
  free(input);
  return 0;
}
