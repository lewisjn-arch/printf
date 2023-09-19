#include "main.h"

/**
 * printable - Checks if a character is printable.
 * @c: Character to be evaluated
 *
 * Return: 1 if the character is printable, 0 otherwise
 */
int printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexacode - Appends the ASCII code in hexadecimal format to buffer
 * @buffer: Array of characters
 * @i: Index at which to start appending
 * @ascii_code: ASCII code to append
 * Return: Always 3
 */
int append_hexacode(char ascii_code, char buffer[], int i)
{
	char map[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map[ascii_code / 16];
	buffer[i] = map[ascii_code % 16];

	return (3);
}

/**
 * digit - Checks if a character is a digit
 * @c: Character to be evaluated
 *
 * Return: 1 if the character is a digit, 0 otherwise
 */
int digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_number_size - Casts a number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted to
 *
 * Return: Casted value of num
 */
long int convert_number_size(long int num, int size)
{
	if (size == S_LONG)
		return (num);

	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_unsigned_size - Casts an unsigned number to the specified size
 * @num: Number to be casted
 * @size: Number indicating the type to be casted to
 *
 * Return: Casted value of num
 */
long int convert_unsigned_size(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);

	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
