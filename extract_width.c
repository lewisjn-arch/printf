#include "main.h"

/**
 * extract_width - Calculates the width for printing
 * @format: Formatted string in which to print the arguments.
 * @i: List of arguments to be printed.
 * @args: list of arguments.
 *
 * Return: width.
 */
int extract_width(const char *format, int *i, va_list args)
{
	int current_index;
	int width = 0;

	for (current_index = *i + 1; format[current_index] != '\0'; current_index++)
	{
		if (digit(format[current_index]))
		{
			width *= 10;
			width += format[current_index] - '0';
		}
		else if (format[current_index] == '*')
		{
			current_i++;
			width = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*i = current_index - 1;

	return (width);
}
