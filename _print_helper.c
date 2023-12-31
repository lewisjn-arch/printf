#include "main.h"

/**
 * handle_character_write - This function prints a string
 * @s: character types.
 * @buffer: Buffer array to handle printing
 * @flags:  This function calculates active flags.
 * @width: gets width for printing.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_character_write(char s, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & FLAGS_ZERO)
		padd = '0';

	buffer[i++] = s;
	buffer[i] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buffer[BUFF_SIZE - i - 2] = padd;

		if (flags & FLAGS_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * number_write - This function prints a string of numbers
 * @negative: Lists of arguments of integers
 * @index: character types.
 * @buffer: Buffer array to handle printing
 * @flags:  This function calculates active flags
 * @width: gets width for printing.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of characters to be printed.
 */
int number_write(int negative, int index, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1;
	char padd = ' ', extra_char = 0;

	UNUSED(size);

	if ((flags & FLAGS_ZERO) && !(flags & FLAGS_MINUS))
		padd = '0';
	if (negative)
		extra_char = '-';
	else if (flags & FLAGS_PLUS)
		extra_char = '+';
	else if (flags & FLAGS_SPACE)
		extra_char = ' ';

	return (num_write(index, buffer, flags, width, precision,
		length, padd, extra_char));
}

/**
 * num_write - This function writes a number using a bufffer
 * @index: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: returns active flags
 * @width: width for printing
 * @prec: Precision specifier
 * @length: Number length
 * @padd: Padding character
 * @extra_char: Extra character
 *
 * Return: Number of printed characters.
 */
int num_write(int index, char buffer[],
	int flags, int width, int prec,
	int length, char padd, char extra_char)
{
	int i, padd_start = 1;

	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0' && width == 0)
		return (0);
	if (prec == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		buffer[index] = padd = ' ';
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--index] = '0', length++;
	if (extra_char != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & FLAGS_MINUS && padd == ' ')
		{
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[index], length) + write(1, &buffer[1], i - 1));
		}
		else if (!(flags & FLAGS_MINUS) && padd == ' ')
		{
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[1], i - 1) + write(1, &buffer[index], length));
		}
		else if (!(flags & FLAGS_MINUS) && padd == '0')
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[index], length - (1 - padd_start)));
		}
	}
	if (extra_char)
		buffer[--index] = extra_char;
	return (write(1, &buffer[index], length));
}

/**
 * unsigned_write - This function writes an unsigned number
 * @negative: Number indicating if the num is negative
 * @index: Index at which the number starts
 * @buffer: Array of characters
 * @flags: returns Flags specifiers
 * @width: Width specifier for printing
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written characters.
 */
int unsigned_write(int negative, int index,
	char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - index - 1, i = 0;
	char padd = ' ';

	UNUSED(negative);
	UNUSED(size);

	if (precision == 0 && index == BUFF_SIZE - 2 && buffer[index] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padd = ' ';

	while (precision > length)
	{
		buffer[--index] = '0';
		length++;
	}

	if ((flags & FLAGS_ZERO) && !(flags & FLAGS_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buffer[i] = padd;

		buffer[i] = '\0';

		if (flags & FLAGS_MINUS)
		{
			return (write(1, &buffer[index], length) + write(1, &buffer[0], i));
		}
		else
		{
			return (write(1, &buffer[0], i) + write(1, &buffer[index], length));
		}
	}

	return (write(1, &buffer[index], length));
}

/**
 * pointer_write - This function writes a memory address
 * @buffer: Arrays of characters
 * @index: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier for printing
 * @flags: Flags specifier
 * @padd: Character representing the padding
 * @extra_char: Character representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int pointer_write(char buffer[], int index, int length,
	int width, int flags, char padd, char extra_char, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buffer[i] = padd;
		buffer[i] = '\0';
		if (flags & FLAGS_MINUS && padd == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[index], length) + write(1, &buffer[3], i - 3));
		}
		else if (!(flags & FLAGS_MINUS) && padd == ' ')
		{
			buffer[--index] = 'x';
			buffer[--index] = '0';
			if (extra_char)
				buffer[--index] = extra_char;
			return (write(1, &buffer[3], i - 3) + write(1, &buffer[index], length));
		}
		else if (!(flags & FLAGS_MINUS) && padd == '0')
		{
			if (extra_char)
				buffer[--padd_start] = extra_char;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], i - padd_start) +
				write(1, &buffer[index], length - (1 - padd_start) - 2));
		}
	}
	buffer[--index] = 'x';
	buffer[--index] = '0';
	if (extra_char)
		buffer[--index] = extra_char;
	return (write(1, &buffer[index], BUFF_SIZE - index - 1));
}
