#include "reset.h"

/**
 * execute_command - function that forks a process and executes a command
 * @comd: the input string
 * Returns: void
 */

void execute_command(char *comd)
{
	pid_t small = fork();
	char exec_path[1024];
	char *path_env = getenv("PATH");

	if (strncmp(comd, "exit", 4) == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strncmp(comd, "setenv", 6) == 0)
	{
		char *args = comd + 6;
		char *context = strtok(args, " \t\n");
		char *value = strtok(NULL, " \t\n");

		if (context != NULL && value != NULL)
		{
			if (setenv(context, value, 1) != 0)
			{
				perror("setenv error");
			}
		}
		else
		{
			fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		}
	}
	else if (strncmp(comd, "cd", 2) == 0)
	{
		char *args = comd + 2;
		char *direc = strtok(args, " \t\n");

		if (direc == NULL)
		{
			direc = getenv("HOME");
		}
		else if (strcmp(direc, "-") == 0)
		{
			direc = getenv("OLDPWD");
		}
		if (direc != NULL)
		{
			char current_direc[1024];

			if (getcwd(current_direc, sizeof(current_direc)) == NULL)
			{
				perror("getcwd error");
				return;
			}
			if (setenv("OLDPWD", current_direc, 1) != 0)
			{
				perror("setenv");
				return;
			}
			if (chdir(direc) != 0)
			{
				perror("chdir error");
				return;
			}
			else
			{
				if (getcwd(current_direc, sizeof(current_direc)) != NULL)
				{
					if (setenv("PWD", current_direc, 1) != 0)
					{
						perror("setenv error");
					}
				}
				else
				{
					perror("getcwd error");
				}
			}
		}
		else 
		{
			fprintf(stderr, "Usage: cd[DIRECTORY]\n");
		}
	}
	else if (strncmp(comd, "unsetenv", 8) == 0)
	{
		char *var = comd + 8;

		if (var != NULL)
		{
			if (unsetenv(var) != 0)
			{
				perror("unsetenv error");
			}
		}
		else
		{
			fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		}
	}
	if (small == -1)
	{
		perror("fork error");
	}
	else if (small == 0)
	{
		char **args = tokenize_input(comd);

		execvp(args[0], args);

		getenv("PATH");

		if (path_env != NULL)
		{
			char *path = strdup(path_env);
			char *dr = strtok(path, ":");

			while (dr != NULL)
			{
				snprintf(exec_path, 1024, "%s/%s", dr, args[0]);
				execvp(exec_path, args);
				dr = strtok(NULL, ":");
			}
			free(path);
		}
		perror("execvp error");
		_exit(EXIT_FAILURE);
	}
	else
	{
		int status;

		waitpid(small, &status, 0);
	}
}

