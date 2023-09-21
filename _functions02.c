#include "main.h"

/**
 * pointer_print - This function prints the value of a pointer variable
 * @args: Lists of arguments to be accesed
 * @buffer: Buffer array to handle printing
 * @flags: this calculates active flags
 * @width: get width for printing
 * @precision: Precision specification value
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int pointer_print(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_char = 0, padd = ' ';
	int index = BUFF_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_address;
	char map_to[] = "0123456789abcdef";
	void *address = va_arg(args, void *);

	UNUSED(width);
	UNUSED(size);

	if (address == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_address = (unsigned long)address;

	while (num_address > 0)
	{
		buffer[index--] = map_to[num_address % 16];
		num_address /= 16;
		length++;
	}

	if ((flags & FLAGS_ZERO) && !(flags & FLAGS_MINUS))
		padd = '0';
	if (flags & FLAGS_PLUS)
		extra_char = '+', length++;
	else if (flags & FLAGS_SPACE)
		extra_char = ' ', length++;

	index++;

	return (pointer_write(buffer, index, length,
		width, flags, padd, extra_char, padd_start));
}

/**
 * non_printable - This function prints ascii codes of non printable
 * characters.
 * @args: Lists of arguments to be accessed
 * @buffer: Buffer array to handle printing
 * @flags: This calculates active flags
 * @width: get width for printing
 * @precision: Precision specification value
 * @size: Size specifier
 * Return: Number of characters printed
 */
int non_printable(va_list args, char buffer[],
	int flags, int width, int precision, int size)
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
 * reverse_print - This function prints a string in reverse
 * @args: Lists of arguments to be accessed
 * @buffer: Buffer array to handle printing
 * @flags: This calculates active flags
 * @width: get width for printing
 * @precision: Precision specification value
 * @size: Size specifier
 * Return: Numbers of characters printed
 */

int reverse_print(va_list args, char buffer[],
	int flags, int width, int precision, int size)
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
		char s = string[i];

		write(1, &s, 1);
		count++;
	}
	return (count);
}

/**
 * rot13string_print - This function prints a string in rot13.
 * @args: Lists of arguments to be accessed
 * @buffer: Buffer array to handle printing
 * @flags: this calculates active flags
 * @width: get width for printing
 * @precision: Precision specification value
 * @size: Size specifier
 * Return: Numbers of characters printed
 */
int rot13string_print(va_list args, char buffer[],
	int flags, int width, int precision, int size)
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
