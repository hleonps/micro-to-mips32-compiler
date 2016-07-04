#include "error_handling.h"

// Imprime los errores de léxico
void lexical_error(int in_char){
	char * line;

	fseek(source, line_info.offset, SEEK_SET);

	line = (char *) malloc (MAX_ALLOCATION_SIZE);
	fgets (line, MAX_ALLOCATION_SIZE, source);

	printf(BOLDRED "Lexical Error: " BOLDWHITE "%c is not defined at line %d:\n" RESET, in_char, line_info.number);
	printf(BOLDWHITE "%s\n" RESET, line);
	
	close_files();

	exit(1);
}

// Imprime los errores de sintaxis
void syntax_error(){
	char * line;

	fseek(source, line_info.offset, SEEK_SET);

	line = (char *) malloc (MAX_ALLOCATION_SIZE);
	fgets (line, MAX_ALLOCATION_SIZE, source);

	printf(BOLDRED "Syntax Error: " RESET);
	printf(BOLDWHITE "at line %d: \n %s\n" RESET, line_info.number, line);
	
	close_files();

	exit(1);
}

// Imprime los errores de semática
void semantic_error(){
	char * line;

	fseek(source, line_info.offset, SEEK_SET);

	line = (char *) malloc (MAX_ALLOCATION_SIZE);
	fgets (line, MAX_ALLOCATION_SIZE, source);

	printf(BOLDRED "Semantic Error: " RESET);
	printf(BOLDWHITE "%s is not defined at line %d: \n %s\n" RESET, token_buffer.token, line_info.number, line);
	
	close_files();

	exit(1);
}

// Cierra los archivos
void close_files(){
	fclose(source);

	if(output){
		fclose(output);
		remove(output_name);
	}
}