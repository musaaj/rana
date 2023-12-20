#include <stdio.h>
#include "lexer.h"

unsigned int length = 0;
unsigned int current = 0;
unsigned int line = 1;
unsigned int column = 0;
bool has_error = false;
char* inputs;

void lexer_error(char* msg) {
  printf("Error: %i : %i; %s\n", line, column, msg);
  has_error = true;
}

char* substr(char* str, unsigned int start, unsigned int end) {
  char* result = malloc(end - start + 1);
  int j = 0;
  if (!result) {
    printf("Error: out of memory");
    exit(EXIT_FAILURE);
  }
  for (; start < end; start++) {
    result[j++] = str[start];
  }
  result[start] = '\0';
  return result;
}

bool is_ident(char c) {
  return isalpha(c) || c == '_';
}

void lexer(char* input) {
  length = strlen(input);
  inputs = input;
  column = 0;
  line = 1;
  current = 0;
}

static char peek_char() {
  return inputs[current];
}

bool eof() {
  return current >= length;
}

static char next_char() {
  char c = inputs[current++];
  if (c == '\n') {
    column = 0;
    line++;
  } else column++;
  return c;
}

static void skip_space() {
  while (isspace(peek_char())) next_char();
}

static token_t* var() {
  unsigned int start = current;
  next_char();
  while (!eof() && (is_ident(peek_char()) || isdigit(peek_char()))) next_char();
  char* str = substr(inputs, start, current);
  token_t* token = new_token(IDENTIFIER, line, column, str);
  return token;
}

static token_t* number() {
  unsigned int start = current;
  while (!eof() && isdigit(peek_char())) next_char();
  if (peek_char() == '.') {
    next_char();
    while (!eof() && isdigit(peek_char())) next_char();
  }
  char* str = substr(inputs, start, current);
  return new_token(NUMBER, line, column, str);
}

static token_t* string() {
  unsigned int start = current;
  next_char();
  while (!eof() && peek_char() != '"') next_char();
  if (eof()) lexer_error("'\"' expected");
  next_char();

  char* str = substr(inputs, start + 1, current - 1);
  return new_token(STRING, line, column, str);
}

token_t* make_token(int type) {
  char* str = substr(inputs, current, current + 1);
  next_char();
  return new_token(type, line, column, str);
}

token_t* peek() {
  unsigned _line = line, _column = column, _current = current;
  token_t* result = NULL;
  skip_space();
  if (is_ident(peek_char())) result = var();
  else if (isdigit(peek_char())) result = number();
  else if (peek_char() == '"') result = string();
  else {
    switch (peek_char()) {
      case '+':
        result = make_token(PLUS); break;
      case '-':
        result = make_token(MINUS); break;
      case '*':
        result = make_token(MUL); break;
      case '/':
        result = make_token(DIV); break;
      case '%':
        result = make_token(MOD); break;;
      case '=':
        result = make_token(EQUAL); break;
      case '(':
        result = make_token(LEFT_PAREN); break;
      case ')':
        result = make_token(RIGHT_PAREN); break;
      default:
        lexer_error("unrecognized token"); next_char(); break;
   }
  }
  line = _line, column = _column, current = _current;
  skip_space();
  return result;
}

token_t* next() {
  token_t* result = NULL;
  skip_space();
  if (is_ident(peek_char())) result = var();
  else if (isdigit(peek_char())) result = number();
  else if (peek_char() == '"') result = string();
  else {
    switch (peek_char()) {
      case '+':
        result = make_token(PLUS); break;
      case '-':
        result = make_token(MINUS); break;
      case '*':
        result = make_token(MUL); break;
      case '/':
        result = make_token(DIV); break;
      case '%':
        result = make_token(MOD); break;;
      case '=':
        result = make_token(EQUAL); break;
      case '(':
        result = make_token(LEFT_PAREN); break;
      case ')':
        result = make_token(RIGHT_PAREN); break;
      default:
        lexer_error("unrecognized token"); next_char(); break;
   }
  }
  skip_space();
  return result;
}
