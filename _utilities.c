#include "main.h"

/**
 * printable - This function evaluates if a character is printable
 * @c: Character to be evaluated.
 *
 * Return: 1 if successful, 0 otherwise
 */
int printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexacode - This function appends ascii in hexadecimal code to buffer
 * @buffer: Array of chars.
 * @i: Index at which to start appending.
 * @ascii: ASCCI CODE.
 * Return: Always 3
 */
int append_hexacode(char ascii, char buffer[], int i)
{
	char map_to[] = "0123456789ABCDEF";

	if (ascii < 0)
		ascii *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = map_to[ascii / 16];
	buffer[i] = map_to[ascii % 16];

	return (3);
}

/**
 * digit - This function verifies if a character is a digit
 * @c: Character to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_number_size - This function casts a number to the specified size
 * @num: The Number to be casted.
 * @size: The Number indicating the type to be casted.
 *
 * Return: The Casted value of num
 */
long int convert_number_size(long int num, int size)
{
	if (size == SIZE_LONG)
		return (num);
	else if (size == SIZE_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_unsigned_size - This function casts a number to the specified size
 * @num: The Number to be casted
 * @size: The Number indicating the type to be casted
 *
 * Return: The Casted value of num
 */
long int convert_unsigned_size(unsigned long int num, int size)
{
	if (size == SIZE_LONG)
		return (num);
	else if (size == SIZE_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
