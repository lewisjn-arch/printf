#include "main.h"

/**
 * print_upper_hexa - Prints an unsigned int in uppercase hexadecimal notation.
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int print_upper_hexa(va_list args, char buffer[], int flags,
                     int width, int precision, int size)
{
    unsigned int num = va_arg(args, unsigned int);
    int i = 0;

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    i += hex_upper_itoa(num, &buffer[i]);

    return (write(1, buffer, i));
}

/**
 * pointer_print - Prints a pointer address in hexadecimal notation.
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
    unsigned long int address = (unsigned long int)va_arg(args, void *);
    int i = 0;

    UNUSED(precision);
    UNUSED(size);

    if (flags & F_ZERO)
    {
        buffer[i++] = '0';
        buffer[i++] = 'x';
    }

    i += hex_long_itoa(address, &buffer[i]);

    return (pointer_write(buffer, i, i, width, flags, ' ', 0, 0));
}

/**
 * non_printable_print - Prints non-printable characters in hexadecimal notation.
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int non_printable_print(va_list args, char buffer[], int flags,
                        int width, int precision, int size)
{
    char *str = va_arg(args, char *);
    int i = 0, length = 0;

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    while (str && str[length])
        length++;

    for (; i < length; i++)
    {
        if (str[i] < 32 || str[i] >= 127)
        {
            buffer[i * 4] = '\\';
            buffer[i * 4 + 1] = 'x';
            buffer[i * 4 + 2] = "0123456789ABCDEF"[((unsigned char)str[i] >> 4) & 0xF];
            buffer[i * 4 + 3] = "0123456789ABCDEF"[(unsigned char)str[i] & 0xF];
        }
        else
            buffer[i] = str[i];
    }

    return (write(1, buffer, i * 4));
}

/**
 * reverse_print - Prints a reversed string.
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int reverse_print(va_list args, char buffer[], int flags,
                  int width, int precision, int size)
{
    char *str = va_arg(args, char *);
    int i = 0, length = 0;

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (str == NULL)
        str = "(null)";

    while (str[length] != '\0')
        length++;

    for (i = length - 1; i >= 0; i--)
        buffer[length - i - 1] = str[i];

    return (write(1, buffer, length));
}

/**
 * rot13string_print - Prints a string with ROT13 encryption.
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int rot13string_print(va_list args, char buffer[], int flags,
                      int width, int precision, int size)
{
    char *str = va_arg(args, char *);
    int i = 0;

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (str == NULL)
        str = "(null)";

    while (str[i] != '\0')
    {
        if ((str[i] >= 'a' && str[i] <= 'z') ||
            (str[i] >= 'A' && str[i] <= 'Z'))
        {
            if ((str[i] >= 'a' && str[i] <= 'm') ||
                (str[i] >= 'A' && str[i] <= 'M'))
                buffer[i] = str[i] + 13;
            else
                buffer[i] = str[i] - 13;
        }
        else
            buffer[i] = str[i];
        i++;
    }

    return (write(1, buffer, i));
}

