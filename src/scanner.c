#include "scanner.h"

const char *reserved_words[] = {
		"begin", "end", "read", "write"};

line_t line_info = {1, 0};

token scanner(void)
{
	int in_char, c;
	clear_buffer();

	if (feof(source))
		return SCANEOF;

	while ((in_char = getc(source)) != EOF)
	{

		// Ignore whitespaces
		if (isspace(in_char))
		{
			if (in_char == '\n')
			{
				line_info.number++;
				line_info.offset = ftell(source);
			}
			continue;
		}
		// Identify IDs and reserved words
		else if (isalpha(in_char))
		{
			buffer_char(in_char);

			for (c = getc(source); isalnum(c) || c == '_'; c = getc(source))
				buffer_char(c);

			ungetc(c, source);
			return check_reserved();
		}
		// Identify integer literals
		else if (isdigit(in_char))
		{
			buffer_char(in_char);

			for (c = getc(source); isdigit(c); c = getc(source))
				buffer_char(c);

			ungetc(c, source);
			return INTLITERAL;
		}
		// Identify left round bracket
		else if (in_char == '(')
		{
			buffer_char(in_char);
			return LPAREN;
		}
		// Identify right round bracket
		else if (in_char == ')')
		{
			buffer_char(in_char);
			return RPAREN;
		}
		// Identify the semicolon (;) of each instruction.
		else if (in_char == ';')
		{
			buffer_char(in_char);
			return SEMICOLON;
		}
		else if (in_char == ',')
		{
			buffer_char(in_char);
			return COMMA;
		}
		else if (in_char == '+')
		{
			buffer_char(in_char);
			return PLUSOP;
		}
		else if (in_char == ':')
		{
			buffer_char(in_char);
			/* looking for ':=' */
			c = getc(source);
			if (c == '=')
			{
				buffer_char(c);
				return ASSIGNOP;
			}
			else
			{
				ungetc(c, source);
				lexical_error(in_char);
			}
		}
		else if (in_char == '-')
		{
			/* looking for '--' */
			c = getc(source);
			if (c == '-')
			{
				while ((in_char = getc(source)) != '\n')
					;
				line_info.number++;
				line_info.offset = ftell(source);
			}
			else if (isdigit(c))
			{

				buffer_char(in_char);
				buffer_char(c);

				for (c = getc(source); isdigit(c); c = getc(source))
					buffer_char(c);

				ungetc(c, source);
				return INTLITERAL;
			}
			else
			{
				buffer_char(in_char);
				ungetc(c, source);
				return MINUSOP;
			}
		}
		else if (in_char == '|')
		{
			buffer_char(in_char);
			return PIPEOP;
		}
		else
		{
			lexical_error(in_char);
		}
	}
	return 0;
}

// Prepares the token buffer.
void buffer_char(char c)
{
	if (token_buffer.token != NULL)
	{
		token_buffer.size++;
		token_buffer.token = (char *)realloc(token_buffer.token, token_buffer.size * sizeof(char));
	}
	else
	{
		token_buffer.token = (char *)calloc(token_buffer.size, sizeof(char));
		token_buffer.size = 1;
	}
	token_buffer.token[token_buffer.size - 1] = c;
}

// Cleans the token buffer
void clear_buffer()
{
	free(token_buffer.token);
	token_buffer.token = NULL;
}

// Verifies if it is a reserved word or an ID.
token check_reserved(void)
{
	for (int i = 0; i < 4; ++i)
	{
		if (!strcmp(reserved_words[i], token_buffer.token))
		{
			switch (i)
			{
			case 0:
				return BEGIN;
			case 1:
				return END;
			case 2:
				return READ;
			case 3:
				return WRITE;
			}
		}
	}
	return ID;
}