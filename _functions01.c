#include "main.h"

/**
 * binary_print - Prints an unsigned int in binary notation.
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int binary_print(va_list args, char buffer[], int flags,
                 int width, int precision, int size)
{
    unsigned int num = va_arg(args, unsigned int);
    int i = 0;

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    i += binary_itoa(num, &buffer[i]);

    return (write(1, buffer, i));
}

/**
 * unsigned_print - Prints an unsigned integer.
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int unsigned_print(va_list args, char buffer[], int flags,
                   int width, int precision, int size)
{
    unsigned int num = va_arg(args, unsigned int);
    int i = 0, negative = 0;
    char padd = ' ';

    UNUSED(size);

    if (precision == 0 && num == 0)
        return (0);

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';

    i += uitoa(num, &buffer[i]);

    return (unsigned_write(negative, i, buffer, flags, width, precision, size));
}

/**
 * octal_print - Prints an unsigned int in octal notation.
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int octal_print(va_list args, char buffer[], int flags,
                int width, int precision, int size)
{
    unsigned int num = va_arg(args, unsigned int);
    int i = 0;

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    i += octal_itoa(num, &buffer[i]);

    return (write(1, buffer, i));
}

/**
 * hexadecimal_print - Prints an unsigned int in lowercase hexadecimal notation.
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int hexadecimal_print(va_list args, char buffer[], int flags,
                      int width, int precision, int size)
{
    unsigned int num = va_arg(args, unsigned int);
    int i = 0;

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    i += hex_itoa(num, &buffer[i]);

    return (write(1, buffer, i));
}

