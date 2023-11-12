#include "reset.h"

/**
 * write_string - function that prints characters in terminal
 * @text: characters to be printed
 * @str: length of character
 * Return: text
 */

ssize_t write_string(int text, const char *str)
{
	return (write(text, str, strlen(str)));
}
