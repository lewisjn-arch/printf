#include "main.h"
/**
 * print_handler - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments.
 * @args: List of arguments to be printed.
 * @i: index.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int handle_print(const char *format, int *i, va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i, unknown_length = 0, printed_characters = -1;
	fmt_t fmt_types[] = {
		{'c', char_print}, {'s', string_print}, {'%', percentage_print},
		{'i', integer_print}, {'d', integer_print}, {'b', binary_print},
		{'u', unsigned_print}, {'o', octal_print}, {'x', hexadecimal_print},
		{'X', print_upper_hexa}, {'p', pointer_print}, {'S', non_printable},
		{'r', reverse_print}, {'R', rot13string_print}, {'\0', NULL}
	};
	for (i = 0; fmt_types[i].format != '\0'; i++)
		if (format[*i] == fmt_types[i].format)
			return (fmt_types[i].fn(args, buffer, flags, width, precision, size));

	if (fmt_types[i].format == '\0')
	{
		if (format[*i] == '\0')
			return (-1);
		unknown_length += write(1, "%%", 1);
		if (format[*i - 1] == ' ')
			unknown_length += write(1, " ", 1);
		else if (width)
		{
			--(*i);
			while (format[*i] != ' ' && format[*i] != '%')
				--(*i);
			if (format[*i] == ' ')
				--(*i);
			return (1);
		}
		unknown_length += write(1, &format[*i], 1);
		return (unknown_length);
	}
	return (printed_characters);
}
