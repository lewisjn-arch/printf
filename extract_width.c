#include "main.h"

/**
 * extract_width - Calculate the width for formatting during printing.
 * @format: The formatted string in which to print the arguments.
 * @i: Pointer to the index tracking the current position in the format string
 * @args: List of arguments
 * Return: The calculated width for formatting.
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
			current_index++;
			width = va_arg(args, int);
			break;
		}
		else
		{
			break;
		}
	}

	*i = current_index - 1;

	return (width);
}
