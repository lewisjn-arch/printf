#include "main.h"

void print_buffer(char buffer[], int *b_index);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_characters = 0;
	int flags, width, precision, size, b_index = 0;
	va_list args;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[b_index++] = format[i];
			if (b_index == BUFF_SIZE)
				buffer_print(buffer, &b_index);
			printed_characters++;
		}
		else
		{
			buffer_print(buffer, &b_index);
			flags = extract_flags(format, &i);
			width = extract_width(format, &i, args);
			precision = extract_precision(format, &i, args);
			size = extract_size(format, &i);
			++i;
			printed = print_handler(format, &i, args, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_characters += printed;
		}
	}

	buffer_print(buffer, &b_index);

	va_end(args);

	return (printed_characters);
}

/**
 * buffer_print - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @b_index: Index at which to add next char, represents the length.
 */
void buffer_print(char buffer[], int *b_index)
{
	if (*b_index > 0)
		write(1, &buffer[0], *_index);

	*b_index = 0;
}
