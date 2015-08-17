#ifndef SCANNER_H
#define SCANNER_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "error_handling.h"

extern const char* reserved_words[];

typedef enum{
	BEGIN, END, READ, WRITE, ID, INTLITERAL,
	LPAREN, RPAREN, SEMICOLON, COMMA, ASSIGNOP,
	PLUSOP, MINUSOP, PIPEOP, SCANEOF
} token;

typedef struct{
	char * token;
	unsigned int size;
} buffer;

/* input code file */
FILE *source;

/* Output code file */
FILE* output;
char * output_name;

typedef struct{
	int number;
	int offset;
} line_t;

const char* reserved_words[4];

buffer token_buffer;
line_t line_info;

token scanner(void);
token check_reserved(void);
void buffer_char(char c);
void clear_buffer(void);

#endif /* SCANNER_H */