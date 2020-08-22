#ifndef SEMANTIC_H
#define SEMANTIC_H

#include <stdio.h>
#include "scanner.h"
#include "error_handling.h"

#define MAXIDLEN 33
#define TABLESIZE 1024

typedef struct
{ /* for operator */
	enum op
	{
		PLUS,
		MINUS
	}
	operator;
} op_rec;

/* expression types */
enum expr
{
	IDEXPR,
	LITERALEXPR,
	TEMPEXPR
};

/* for <primary> and <expression> */
typedef struct
{
	enum expr kind;
	union {
		char *name; /* for IDEXPR, TEMPEXPR */
		int val;		/* for LITERALEXPR */
	};
} expr_rec;

char symbol_table[TABLESIZE][MAXIDLEN];

FILE *tmp_data_seg;

/* Is it in the symbol table? */
extern int lookup(char *s);

/* Puts unconditionally into symbol table */
extern void enter(char *s);

char *get_temp(void);
char *get_label(void);
void start(void);
void finish(void);
void assign(expr_rec target, expr_rec source);

void write_jump(char *label, expr_rec expr);
void write_label(char *label);
void extrict_jump(char *label);

expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2);
void read_id(expr_rec in_var);
expr_rec process_id(char *token);
expr_rec process_temp(char *token);
expr_rec process_literal(char *token);
op_rec process_op();
void write_expr(expr_rec out_expr);

char *extract(expr_rec expr);
char *extract_op(op_rec expr);

#endif /* SEMANTIC_H */