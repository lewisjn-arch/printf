#include "main.h"

/**
 * pointer_print - Prints the value of a pointer variable
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int pointer_print(va_list args, char buffer[], int flags,
		int width, int precision, int size)
{
	char extra_char = 0, padd = ' ';
	int i = BUFFER_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_address;
	char map[] = "0123456789abcdef";
	void *address = va_arg(args, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFFER_SIZE - 1] = '\0';
	UNUSED(precision);

	num_address = (unsigned long)address;

	while (num_address > 0)
	{
		buffer[i--] = map[num_address % 16];
		num_address /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_char = '+', length++;
	else if (flags & F_SPACE)
		extra_char = ' ', length++;

	i++;

	return (pointer_write(buffer, i, length, width,
		flags, padd, extra_char, padd_start));
}

/**
 * non_printable_print - Prints ASCII codes in hexadecimal
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int non_printable_print(va_list args, char buffer[], int flags,
			int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *string = va_arg(args, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (string == NULL)
		return (write(1, "(null)", 6));

	while (string[i] != '\0')
	{
		if (printable(string[i]))
			buffer[i + offset] = string[i];
		else
			offset += append_hexacode(string[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/**
 * reverse_print - Prints a reverse string.
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int reverse_print(va_list args, char buffer[], int flags,
		int width, int precision, int size)
{
	char *string;
	int i, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	string = va_arg(args, char *);

	if (string == NULL)
	{
		UNUSED(precision);

		string = ")Null(";
	}
	for (i = 0; string[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char n = string[i];

		write(1, &n, 1);
		count++;
	}
	return (count);
}

/**
 * rot13string_print - Prints a string in ROT13.
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int rot13string_print(va_list args, char buffer[], int flags,
			int width, int precision, int size)
{
	char c;
	char *string;
	unsigned int i, j;
	int count = 0;
	char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char output[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	string = va_arg(args, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (string == NULL)
		string = "(AHYY)";
	for (i = 0; string[i]; i++)
	{
		for (j = 0; input[j]; j++)
		{
			if (input[j] == string[i])
			{
				c = output[j];
				write(1, &c, 1);
				count++;
				break;
			}
		}
		if (!input[j])
		{
			c = string[i];
			write(1, &c, 1);
			count++;
		}
	}
	return (count);
}
