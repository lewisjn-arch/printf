#include "main.h"

/**
 * unsigned_print - This functions prints an unsigned number
 * @args: Lists of arguments to be accessed
 * @buffer: Buffer array to handle printing
 * @flags: this calculates active flags
 * @width: get width for printing
 * @precision: Precision specification value
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int unsigned_print(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	int index = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);

	num = convert_unsigned_size(num, size);

	if (num == 0)
		buffer[index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[index--] = (num % 10) + '0';
		num /= 10;
	}

	index++;

	return (unsigned_write(0, index, buffer, flags, width, precision, size));
}

/**
 * octal_print - This function prints an unsigned number in octal notation
 * @args: Lists of arguments to be accessed
 * @buffer: Buffer array to handle printing
 * @flags: this calculates active flags
 * @width: get width to be printed
 * @precision: Precision specification value
 * @size: Size specifier
 * Return: Number of characters printed
 */
int octal_print(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{

	int index = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_unsigned_size(num, size);

	if (num == 0)
		buffer[index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[index--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & FLAGS_HASH && init_num != 0)
		buffer[index--] = '0';

	index++;

	return (unsigned_write(0, index, buffer, flags, width, precision, size));
}

/**
 * hexadecimal_print - This function prints an unsigned
 * number in hexadecimal notation
 * @args: Lists of arguments to be accessed
 * @buffer: Buffer array to handle printing
 * @flags: this calculates active flags
 * @width: get width for printing
 * @precision: Precision specification value
 * @size: Size specifier
 * Return: Number of characters printed
 */
int hexadecimal_print(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (hexa_print(args, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**
 * print_upper_hexa - This function prints an unsigned number
 * in upper hexadecimal notation
 * @args: Lists of arguments to be accessed
 * @buffer: Buffer array to handle printing
 * @flags: This calculates active flags
 * @width: get width for printing
 * @precision: Precision specification value
 * @size: Size specifier
 * Return: Number of characters printed
 */
int print_upper_hexa(va_list args, char buffer[],
	int flags, int width, int precision, int size)
{
	return (hexa_print(args, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**
 * hexa_print - This function prints a hexadecimal number in lower or upper
 * @args: Lists of arguments to be printed
 * @map_to: Array to map the number
 * @buffer: Buffer array to handle printing
 * @flags: This calculates active flags
 * @flag_char: This calculates active flags in the string
 * @width: get width for printing
 * @precision: Precision specification value
 * @size: Size specification
 * Return: Number of characters printed
 */
int hexa_print(va_list args, char map_to[], char buffer[],
	int flags, char flag_char, int width, int precision, int size)
{
	int index = BUFF_SIZE - 2;
	unsigned long int num = va_arg(args, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_unsigned_size(num, size);

	if (num == 0)
		buffer[index--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[index--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & FLAGS_HASH && init_num != 0)
	{
		buffer[index--] = flag_char;
		buffer[index--] = '0';
	}

	index++;

	return (unsigned_write(0, index, buffer, flags, width, precision, size));
}
