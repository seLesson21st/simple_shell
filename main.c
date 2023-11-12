#include "reset.h"

/**
 * main -  function that prompts user for input
 * @argc: number of arguments passed in
 * @argv: array of argument strings
 * Return: Always 0
 */

int main(int argc, char *argv[])
{
	char input[1024];
	char *line;
	size_t len = 0;
	ssize_t y;
	int x;

	if (isatty(STDIN_FILENO))
	{
		while (1)
		{
			write_string(STDOUT_FILENO, "A$ ");
			line = fgets(input, sizeof(input), stdin);
			if (line == NULL)
			{
				break;
			}
			line[strcspn(line, "\n")] = '\0';

			if (strcmp(line, "exit") == 0)
			{
				break;
			}
			else
			{
				execute_commands(line);
			}
		}
	}
	else if (argc > 1)
	{
		for (x = 1; x < argc; x++)
		{
			execute_commands(argv[x]);
		}
	}
	else
	{
		char *line = NULL;

		while ((y = getline(&line, &len, stdin)) != -1)
		{
			line[strcspn(line, "\n")] = '\0';
			execute_commands(line);
		}
		free(line);
	}

	return (0);
}
