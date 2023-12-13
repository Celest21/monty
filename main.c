#include "monty.h"

int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned int line_number = 0;
	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (!file)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++;

		if (strcmp(line, "pall\n") == 0)
		{
			pall(&stack, line_number);
		}
		else if (strncmp(line, "push ", 5) == 0)
		{
			int value = atoi(line + 5);

			if (value == 0 && line[5] != '0')
			{
				fprintf(stderr, "L%d: usage: push integer\n", line_number);
				exit(EXIT_FAILURE);
			}

			push(&stack, value, line_number);
		}
		/*Add more opcode handling as needed*/
		else
		{
			fprintf(stderr, "L%d: unknown instruction %s", line_number, line);
			exit(EXIT_FAILURE);
		}
	}

	free(line);
	fclose(file);
	return 0;
}

