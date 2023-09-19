#include "main.h"

/**
 * extract_size - Determine the data type size for the argument
 * @format: Formatted string to print arguments.
 * @i: Pointer to track the current format position.
 *
 * Return: Size for data type casting, 0 if none specified
 */
int extract_size(const char *format, int *i)
{
	int current_index = *i + 1;
	int size = 0;

	if (format[current_index] == 'l')
		size = S_LONG;
	else if (format[current_index] == 'h')
		size = S_SHORT;

	if (size == 0)
		*i = current_index - 1;
	else
		*i = current_index;

	return (size);
}
