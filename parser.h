#ifndef PARSER_H
#define PARSER_H

#include "scanner.h"
#include "semantics.h"
#include "error_handling.h"

#define COND_FLAG_ON 1
#define COND_FLAG_OFF 0

token current_token;
token *tmp_token;


void system_goal(void);
void program(void);
void statement_list(void);
void statement(void);
void id_list(void);
void expression(expr_rec *target, int condicional);
void expr_list();
void condicional(expr_rec *target, token t);
op_rec add_op(void);
expr_rec primary(expr_rec target);

void match(token tok);
token next_token(void);

#endif /* PARSER_H */