#include "main.h"

void buffer_print(char buffer[], int *b_index);

/**
 * _printf - This function is a custom Printf function
 * @format: format.
 * Return: Printed characters to standard output.
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
 * buffer_print - This function prints the contents of the buffer
 * @buffer: Array of characters to be printed
 * @b_index: Index at which to add next character, represents the length.
 */
void buffer_print(char buffer[], int *b_index)
{
	if (*b_index > 0)
		write(1, &buffer[0], *b_index);

	*b_index = 0;
}
