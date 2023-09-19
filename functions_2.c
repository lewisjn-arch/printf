#include "main.h"

/**
 * print_unsigned - Prints an unsigned integer
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_unsigned(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    unsigned int n = va_arg(args, unsigned int);

    return (write_number(1, n, buffer, flags, width, precision, size));
}

/**
 * print_octal - Prints an integer in octal
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_octal(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    unsigned int n = va_arg(args, unsigned int);
    char map_to[] = "01234567";

    return (print_hexa(args, map_to, buffer, flags, '0', width, precision, size));
}

/**
 * print_hexadecimal - Prints an integer in hexadecimal
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_hexadecimal(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    unsigned int n = va_arg(args, unsigned int);
    char map_to[] = "0123456789abcdef";

    return (print_hexa(args, map_to, buffer, flags, '0', width, precision, size));
}

/**
 * print_hexa_upper - Prints an integer in uppercase hexadecimal
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_hexa_upper(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    unsigned int n = va_arg(args, unsigned int);
    char map_to[] = "0123456789ABCDEF";

    return (print_hexa(args, map_to, buffer, flags, '0', width, precision, size));
}

/**
 * print_non_printable - Prints non-printable characters in hexadecimal
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_non_printable(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    char *str = va_arg(args, char *);
    int i, len = 0, printed = 0;

    if (str == NULL)
    {
        str = "(null)";
        len = 6;
    }
    else
    {
        for (i = 0; str[i]; i++)
        {
            if (str[i] < 32 || str[i] >= 127)
                len += 4;
            else
                len++;
        }
    }

    if (precision >= 0 && precision < len)
        len = precision;
    if (width > len && !(flags & F_MINUS))
        printed += handle_write_string(' ', buffer, flags, width - len, size);
    for (i = 0; *str && (precision == -1 || i < precision); i++)
    {
        if (*str < 32 || *str >= 127)
            printed += handle_write_hexa(*str, buffer, flags, size);
        else
            printed += handle_write_char(*str, buffer, flags, size);
        str++;
    }
    if (width > len && (flags & F_MINUS))
        printed += handle_write_string(' ', buffer, flags, width - len, size);

    return (printed);
}
