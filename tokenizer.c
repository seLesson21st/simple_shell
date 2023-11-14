#include "reset.h"

/**
 * tokenize_input - function that breaks a string into
 * an array of tokens
 * @input: string to be broken;
 * Return: array of tokens
 */

char **tokenize_input(const char *input)
{
	char *copy = strdup(input);
	char *current_token = strtok(copy, " \t\n");
	char **tokens;
	size_t token_count = 0;
	size_t i = 0;

	while (current_token != NULL)
	{
		token_count++;
		current_token = strtok(NULL, " \t\n");
	}

	tokens = (char **)malloc((token_count + 1) * sizeof(char *));
	if (tokens == NULL)
	{
		perror("malloc error");
		free(copy);
		exit(EXIT_FAILURE);
	}

	strcpy(copy, input);
	current_token = strtok(copy, " \t\n");

	while (current_token != NULL)
	{
		tokens[i] = strdup(current_token);
		current_token = strtok(NULL, " \t\n");
		i++;
	}

	tokens[i] = NULL;
	free(copy);
	return (tokens);
}
