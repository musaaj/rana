#ifndef RANA_TOKEN
#define RANA_TOKEN
#include "rana.h"
#define MIN_LIST_CAPACITY 20;

typedef enum {
	NUMBER, STRING, IDENTIFIER,

	PLUS, MINUS, MUL, DIV, MOD, POWER,

	BITWISE_AND, BITWISE_OR, BITWISE_LEFT_SHIFT, BITWISE_RIGHT_SHIFT, BITWISE_NOT,

	EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL, NOT_EQUAL,

	AND, OR, NOT,

	COMMA, SEMICOLON, LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, LEFT_BRACKET, RIGHT_BRACKET,

	LET, IF, WHILE, FOR, FUN, CLASS, RETURN, BREAK, CONTINUE, NEW, EXTENDS, ENUM
} token_type;

typedef struct {
	int type;
	int line;
	int column;
	char *value;
} token_t;

typedef struct {
	int capacity;
	int length;
	token_t** list;
} token_list;

token_t* new_token(int type, int line, int column, char* token);
void add_token(int type, int line, int column, char* token);
void free_token(token_t* token);
token_list* new_token_list();
void print_token(token_t*);
bool eof();
token_t* next();
token_t* peek();

#endif
