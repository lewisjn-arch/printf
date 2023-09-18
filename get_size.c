#include "main.h"

/**
 * get_size - Determine the data type size for the argument
 * @format: Formatted string to print arguments.
 * @i: Pointer to track the current format position.
 *
 * Return: Size for data type casting, 0 if none specified
 */
int get_size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = S_LONG;
	else if (format[curr_i] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	return (size);
}
