#include "main.h"

void buffer_print(char buffer[], int *buff_index);

/**
 * _printf - Custom printf function
 * @format: The format string.
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_characters = 0;
	int flags, width, precision, size, buff_index = 0;
	va_list args;
	char buffer[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff_index++] = format[i];
			if (buff_index == BUFFER_SIZE)
				buffer_print(buffer, &buff_index);
			printed_characters++;
		}
		else
		{
			buffer_print(buffer, &buff_index);
			flags = extract_flags(format, &i);
			width = extract_width(format, &i, args);
			precision = extract_precision(format, &i, args);
			size = extract_size(format, &i);
			++i;
			printed = _print_handler(format, &i, args, buffer,
					flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_characters += printed;
		}
	}
	buffer_print(buffer, &buff_index);

	va_end(args);

	return (printed_characters);
}

/**
 * buffer_print - This function prints the contents of the buffer if it exists
 * @buffer: Array of characters stored in the buffer
 * @buff_index: Index at which to add the proceeding character.
 */
void buffer_print(char buffer[], int *buff_index)
{
	if (*buff_index > 0)
		write(1, &buffer[0], *buff_index);
	*buff_index = 0;
}
