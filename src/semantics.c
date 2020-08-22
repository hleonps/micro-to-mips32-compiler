#include "semantics.h"
#include "parser.h"

/**
 * Lookups if a variable has been previously defined.
 */
int lookup(char *s)
{
	char *symbol;
	for (int i = 0; i < TABLESIZE; i++)
	{
		symbol = symbol_table[i];
		if (symbol != NULL && strcmp(symbol, s) == 0)
		{
			return 1;
		}
	}
	return 0;
}

/**
 * Adds a variable to the symbol table
 */
void enter(char *s)
{
	static int index = 0;
	strcpy(symbol_table[index], s);
	index++;
}

char *get_temp()
{
	// Max temporary allocated so far
	static int max_temp = 0;
	static char tempname[MAXIDLEN];
	if (max_temp == 10)
		max_temp = 0;
	sprintf(tempname, "$t%d", max_temp);
	max_temp++;
	return tempname;
}

char *get_label()
{
	// Max label allocated so far
	static int max_label = 0;
	static char label[MAXIDLEN];

	sprintf(label, ".label%d", max_label);
	max_label++;

	return label;
}

void start()
{
	// Semantic initializations
	output = fopen(output_name, "w");
	if (output != NULL)
	{
		tmp_data_seg = tmpfile();
		fprintf(tmp_data_seg, ".data\n");

		fprintf(output, ".text\n");
		fprintf(output, ".globl main\n");
		fprintf(output, "main:\n");
	}
	else
	{
		printf("Unknown error");
		exit(-1);
	}
}

void finish()
{
	// Generate code to finish program
	fprintf(output, "li $v0, 10\n");
	fprintf(output, "syscall\n");
	fprintf(output, "\n");
	long lSize;
	char *buffer;
	size_t result;

	// Obtain file size
	fseek(tmp_data_seg, 0, SEEK_END);
	lSize = ftell(tmp_data_seg);
	rewind(tmp_data_seg);

	// Allocate memory to contain the whole file
	buffer = (char *)malloc(sizeof(char) * lSize);
	// Copy the file into the buffer
	result = fread(buffer, 1, lSize, tmp_data_seg);
	if (result != lSize)
	{
		fputs("Reading error", stderr);
		exit(3);
	}

	// The whole file is now loaded in the memory buffer
	fprintf(output, "%s\n", buffer);
}

/**
 * Writes a value assignment into the assembly file.
 */
void assign(expr_rec target, expr_rec source_expr)
{
	/* Generate code for assigment */
	if (source_expr.kind == LITERALEXPR && target.kind == IDEXPR)
	{
		if (!lookup(target.name))
		{
			enter(target.name);
			fprintf(tmp_data_seg, "%s: .word %s\n", target.name, extract(source_expr));
		}
		else
		{
			char *tmp_reg = get_temp();
			fprintf(output, "li %s, %s\n", tmp_reg, extract(source_expr));
			fprintf(output, "sw %s, %s\n", tmp_reg, target.name);
		}
	}

	if (source_expr.kind == LITERALEXPR && target.kind == TEMPEXPR)
	{
		fprintf(output, "li %s, %s\n", target.name, extract(source_expr));
	}

	if (source_expr.kind == IDEXPR && target.kind == TEMPEXPR)
	{
		fprintf(output, "lw %s, %s\n", target.name, extract(source_expr));
	}

	if (source_expr.kind == IDEXPR && target.kind == IDEXPR)
	{
		char *tmp_reg = get_temp();
		if (!lookup(target.name))
		{
			enter(target.name);
			fprintf(tmp_data_seg, "%s: .space %d\n", target.name, 4);
		}
		fprintf(output, "lw %s, %s\n", tmp_reg, extract(source_expr));
		fprintf(output, "sw %s, %s\n", tmp_reg, target.name);
	}

	if (source_expr.kind == TEMPEXPR && target.kind == IDEXPR)
	{
		if (!lookup(target.name))
		{
			enter(target.name);
			fprintf(tmp_data_seg, "%s: .space %d\n", target.name, 4);
		}
		fprintf(output, "sw %s, %s\n", extract(source_expr), target.name);
	}

	if (source_expr.kind == TEMPEXPR && target.kind == TEMPEXPR)
	{
		fprintf(output, "move %s, %s\n", target.name, extract(source_expr));
	}
}

/**
 * Writes a jump to label, into the assembly file.
 */
void write_jump(char *label, expr_rec expr)
{
	char *zero_reg = malloc(3);
	strcpy(zero_reg, get_temp());

	fprintf(output, "li %s, %d\n", zero_reg, 0);

	if (expr.kind != TEMPEXPR)
	{
		char *temp_reg = malloc(3);

		if (expr.kind == LITERALEXPR)
		{
			strcpy(temp_reg, get_temp());
			fprintf(output, "li %s, %d\n", temp_reg, expr.val);
		}
		else
		{
			strcpy(temp_reg, get_temp());
			fprintf(output, "lw %s, %s\n", temp_reg, expr.name);
		}

		fprintf(output, "beq %s, %s, %s\n", temp_reg, zero_reg, label);
	}
	else
	{
		fprintf(output, "beq %s, %s, %s\n", expr.name, zero_reg, label);
	}
}

/**
 * Writes a label, into the assembly file.
 */
void write_label(char *label)
{
	fprintf(output, "%s:\n", label);
}

// Writes extrict jumps to label, into the assembly file.
void extrict_jump(char *label)
{
	fprintf(output, "j %s\n", label);
}

op_rec process_op()
{
	/* Produce operator descriptor */
	op_rec o;

	o.operator=(current_token == PLUSOP) ? PLUS : MINUS;

	return o;
}

// Writes the operations into, the assembly file
expr_rec gen_infix(expr_rec e1, op_rec op, expr_rec e2)
{
	expr_rec e_rec;

	// Constant Folding
	if (e1.kind == LITERALEXPR && e2.kind == LITERALEXPR)
	{

		e_rec.kind = LITERALEXPR;
		e_rec.val = (op.operator== PLUS) ? e1.val + e2.val : e1.val - e2.val;
	}
	else
	{

		/* An expr_rec with temp variant set */
		e_rec.kind = TEMPEXPR;

		/*
		 * Generate code for infix operation.
		 * Get result temp and set up semantic record
		 * for result
		 */
		char *tmp = get_temp();
		e_rec.name = malloc(sizeof(tmp));

		strcpy(e_rec.name, tmp);
		char *tmp_reg1 = malloc(3);

		char *tmp_reg2 = malloc(3);

		if (e1.kind == LITERALEXPR)
		{
			strcpy(tmp_reg1, get_temp());
			fprintf(output, "li %s, %d\n", tmp_reg1, e1.val);
		}
		else if (e1.kind == IDEXPR)
		{
			strcpy(tmp_reg1, get_temp());
			fprintf(output, "lw %s, %s\n", tmp_reg1, e1.name);
		}
		else
		{
			strcpy(tmp_reg1, get_temp());
			fprintf(output, "move %s, %s\n", tmp_reg1, e1.name);
		}

		if (e2.kind == LITERALEXPR)
		{
			strcpy(tmp_reg2, get_temp());
			fprintf(output, "li %s, %d\n", tmp_reg2, e2.val);
		}
		else if (e2.kind == IDEXPR)
		{
			strcpy(tmp_reg2, get_temp());
			fprintf(output, "lw %s, %s\n", tmp_reg2, e2.name);
		}
		else
		{
			strcpy(tmp_reg2, get_temp());
			fprintf(output, "move %s, %s\n", tmp_reg2, e2.name);
		}

		fprintf(output, "%s %s, %s, %s\n", extract_op(op), e_rec.name, tmp_reg1, tmp_reg2);
	}

	return e_rec;
}

// Write operation to read from the stdin.
void read_id(expr_rec in_var)
{
	/* Generate code for read. */
	fprintf(output, "li $v0, 5\n");
	fprintf(output, "syscall\n");
	fprintf(output, "sw $v0, %s\n", extract(in_var));
}

expr_rec process_id(char *token)
{
	expr_rec t;

	/*
	 * Declare ID and build a
	 * corresponding semantic record.
	 */
	t.kind = IDEXPR;
	t.name = malloc(sizeof(token));
	strcpy(t.name, token);
	return t;
}

expr_rec process_temp(char *token)
{
	expr_rec t;

	/*
	 * Declare ID and build a
	 * corresponding semantic record.
	 */
	t.kind = TEMPEXPR;
	t.name = malloc(sizeof(token));
	strcpy(t.name, token);
	return t;
}

expr_rec process_literal(char *token)
{
	expr_rec t;

	/*
	 * Convert literal to a numeric representation
	 * and build semantic record.
	 */
	t.kind = LITERALEXPR;
	sscanf(token, "%d", &t.val);
	return t;
}

// Writes expression, into the file.
void write_expr(expr_rec out_expr)
{
	fprintf(output, "li $v0, 1\n");
	if (out_expr.kind == LITERALEXPR)
		fprintf(output, "li $a0, %s\n", extract(out_expr));
	else
		fprintf(output, "move $a0, %s\n", extract(out_expr));
	fprintf(output, "syscall\n");
	fprintf(output, "li $a0, 10\n");
	fprintf(output, "li $v0, 11\n");
	fprintf(output, "syscall\n");
}

// Extracts the information of an expression.
char *extract(expr_rec expr)
{
	char *data = NULL;
	if (expr.kind == IDEXPR || expr.kind == TEMPEXPR)
	{
		data = expr.name;
	}
	else
	{
		data = malloc(sizeof(int));
		sprintf(data, "%d", expr.val);
	}
	return data;
}

// Extract the operation from an expression.
char *extract_op(op_rec op)
{
	char *operation = (op.operator== PLUS) ? "add" : "sub";
	return operation;
}
