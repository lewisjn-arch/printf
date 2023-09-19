#include "main.h"

/**
 * print_binary - Prints an integer in binary
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_binary(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    unsigned int n = va_arg(args, unsigned int);
    char map_to[] = "01";

    return (print_hexa(args, map_to, buffer, flags, '0', width, precision, size));
}

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
 * print_percentage - Prints a percentage character
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_percentage(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    (void)args;
    if (width > 0 && !(flags & F_MINUS) && !(flags & F_ZERO))
        return (handle_write_string(' ', buffer, flags, width - 1, size) + handle_write_char('%', buffer, flags, size));
    if (width > 0 && (flags & F_MINUS))
        return (handle_write_char('%', buffer, flags, size) + handle_write_string(' ', buffer, flags, width - 1, size));
    return (handle_write_char('%', buffer, flags, size));
}

