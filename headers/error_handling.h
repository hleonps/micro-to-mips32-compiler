#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include "constants.h"
#include "scanner.h"


void lexical_error(int in_char);
void syntax_error(void);
void semantic_error(void);
void close_files(void);

#endif /* ERROR_HANDLING_H */