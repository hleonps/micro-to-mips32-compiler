#include "scanner.h"
#include "parser.h"

char *remove_extension(const char *filename);

int main(int argc, char const *argv[])
{
	source = fopen(argv[1], "r");

	if (source != NULL)
	{
		output_name = remove_extension(argv[1]);
		sprintf(output_name, "%s.asm", output_name); // Add .asm extesion to output file.

		system_goal();

		fclose(source);
		fclose(output);

		return 0;
	}
	else
	{
		printf("Error abriendo el archivo '%s'\n", argv[1]);
		return 1;
	}
}

// Removes the extension (.) of the filename.
char *remove_extension(const char *filename)
{
	char *result;
	char *lastdot;

	if (filename == NULL)
		return NULL;

	if ((result = malloc(strlen(filename) + 1)) == NULL)
		return NULL;

	strcpy(result, filename);
	lastdot = strrchr(result, '.');

	if (lastdot != NULL)
		*lastdot = '\0';

	return result;
}
