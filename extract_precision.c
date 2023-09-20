#include "main.h"

/**
 * extract_precision - This function calculates the precision
 * @format: string in which to print the arguments
 * @i: List of arguments to be printed.
 * @args: list of arguments.
 *
 * Return: Precision.
 */
int extract_precision(const char *format, int *i, va_list args)
{
	int current_index = *i + 1;
	int precision = -1;

	if (format[current_index] != '.')
		return (precision);

	precision = 0;

	for (current_index += 1; format[current_index] != '\0'; current_index++)
	{
		if (digit(format[current_index]))
		{
			precision *= 10;
			precision += format[current_index] - '0';
		}
		else if (format[current_index] == '*')
		{
			current_index++;
			precision = va_arg(args, int);
			break;
		}
		else
			break;
	}

	*i = current_index - 1;

	return (precision);
}
