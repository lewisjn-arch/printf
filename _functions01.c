#include "main.h"

/**
 * unsigned_print - Prints an unsigned number
 * @args: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int unsigned_print(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);

	num = convert_unsigned_size(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (unsigned_write(0, index, buffer, flags, width, precision, size));
}

/**
 * octal_print - Prints an unsigned number in octal notation
 * @args: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int octal_print(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_unsigned_size(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & FLAGS_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (unsigned_write(0, index, buffer, flags, width, precision, size));
}

/**
 * hexadecimal_print - Prints an unsigned number in hexadecimal notation
 * @args: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int hexadecimal_print(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (hexa_print(args, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_upper_hexa - Prints an unsigned number in upper hexadecimal notation
 * @args: Lists of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_upper_hexa(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (hexa_print(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * hexa_print - Prints a hexadecimal number in lower or upper
 * @args: Lists of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int hexa_print(va_list args, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_unsigned_size(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & FLAGS_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (unsigned_write(0, index, buffer, flags, width, precision, size));
}
