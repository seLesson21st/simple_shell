#include "reset.h"

/**
 * execute_commands - function that execute commands
 * @commands: to be executed
 * Return: void
 */

void execute_commands(char *commands)
{
	char *delimiter = "; ";
	char *command = strtok(commands, delimiter);
	int status;

	while (command != NULL)
	{
		char *logic_and = strstr(command, "&&");
		char *logic_or = strstr(command, "||");

		if (logic_and != NULL || logic_or != NULL)
		{
			char *left_command = strtok(command, logic_and != NULL ? "&" : "|");
			char *right_command = strtok(NULL, "");

			strtok(NULL, logic_and != NULL ? "&" : "|");
			execute_command(left_command);

			wait(&status);

			if ((logic_and != NULL && WIFEXITED(status) && WEXITSTATUS(status) == 0) ||
					(logic_or != NULL && (!WIFEXITED(status) || WEXITSTATUS(status) != 0))) {
				execute_command(right_command);
			}
		}
		else
		{
			execute_command(command);
		}
		command = strtok(NULL, delimiter);
		if (isatty(STDIN_FILENO))
			write_string(STDOUT_FILENO, "A$ ");
	}
}
