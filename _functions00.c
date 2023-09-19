#include "main.h"

/**
 * char_print - Prints a character
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int char_print(va_list args, char buffer[], int flags,
		int width, int precision, int size)
{
	char c = va_arg(args, int);

	return (handle_character_write(c, buffer, flags,
		width, precision, size));
}

/**
 * string_print - Prints a string
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int string_print(va_list args, char buffer[],
		int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *string = va_arg(args, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (string == NULL)
	{
		string = "(null)";
		if (precision >= 6)
			string = "      ";
	}
	while (string[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &string[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &string[0], length);
			return (width);
		}
	}
	return (write(1, string, length));
}

/**
 * percentage_print- Prints a percent sign
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int percentage_print(va_list args, char buffer[], int flags,
		int width, int precision, int size)
{
	UNUSED(args);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**
 * integer_print - Print an integer
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int integer_print(va_list args, char buffer[], int flags,
		int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	int negative = 0;
	long int n = va_arg(args, long int);
	unsigned long int num;

	n = convert_number_size(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (number_write(negative, i, buffer, flags,
				width, precision, size));
}

/**
 * binary_print - Prints an unsigned number in binary
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int binary_print(va_list args, char buffer[], int flags,
		int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int arr[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(args, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	arr[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		arr[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += arr[i];
		if (sum || i == 31)
		{

			char j = '0' + arr[i];

			write(1, &j, 1);

			count++;
		}
	}
	return (count);
}

