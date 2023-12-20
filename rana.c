#include <stdio.h>
#include "rana.h"
#include "lexer.h"
#include "token_types.h"
#include "expr.h"

int main(int argc, char** argv) {
  char* input = NULL;
  size_t c = 1024;
  if (argc != 2) {
    printf("Rana v0.0.1\n");
    while (1) {
      printf(">> ");
      getline(&input, &c, stdin);
      *(input + (strlen(input) - 1)) = 0;
      lexer(input);
      //while (!eof()) print_token(next());
      expr_t* expr = parse_expr();
      pretty_print(expr);
      printf("\n");
    }
  } else {
    printf("%s run\n", argv[1]);
  }
  free(input);
  return 0;
}
