#include "main.h"

/**
 * extract_size - Calculates the size to cast the argument
 * @format: Formatted string in which to print the arguments
 * @i: List of arguments to be printed.
 *
 * Return: Precision.
 */
int extract_size(const char *format, int *i)
{
	int current_index = *i + 1;
	int size = 0;

	if (format[current_index] == 'l')
		size = SIZE_LONG;
	else if (format[current_index] == 'h')
		size = SIZE_SHORT;

	if (size == 0)
		*i = current_index - 1;
	else
		*i = currend_index;

	return (size);
}
