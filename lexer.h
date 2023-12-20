#ifndef LEXER_H
#define LEXER_H
#include <stdbool.h>
#include "rana.h"
#include "token_types.h"

token_t* peek();
token_t* next();
void lexer(char* input);

#endif
