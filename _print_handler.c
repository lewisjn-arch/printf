#include "main.h"
/**
 * print_handler - This function prints an argument based on its type
 * @format: string in which to print the arguments.
 * @args: List of arguments to be printed.
 * @index: index.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: gets width to be printed.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: 1 or 2;
 */
int print_handler(const char *format, int *index, va_list args, char buffer[],
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
		if (format[*index] == fmt_types[i].format)
			return (fmt_types[i].fn(args, buffer, flags, width, precision, size));

	if (fmt_types[i].format == '\0')
	{
		if (format[*index] == '\0')
			return (-1);
		unknown_length += write(1, "%%", 1);
		if (format[*index - 1] == ' ')
			unknown_length += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (format[*index] != ' ' && format[*index] != '%')
				--(*index);
			if (format[*index] == ' ')
				--(*index);
			return (1);
		}
		unknown_length += write(1, &format[*index], 1);
		return (unknown_length);
	}
	return (printed_characters);
}
