#include "main.h"

/**
 * handle_print - Handles format specifiers and calls the appropriate function
 * @fmt: Format string
 * @i: Current index in format string
 * @list: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int handle_print(const char *fmt, int *i, va_list list, char buffer[], int flags, int width, int precision, int size)
{
    int j, printed = 0;
    fmt_t arr[] = {
        {'c', print_char},
        {'s', print_string},
        {'d', print_int},
        {'i', print_int},
        {'b', print_binary},
        {'u', print_unsigned},
        {'o', print_octal},
        {'x', print_hexadecimal},
        {'X', print_hexa_upper},
        {'S', print_non_printable},
        {'p', print_pointer},
        {'r', print_reverse},
        {'R', print_rot13string},
        {'\0', NULL},
    };

    for (j = 0; arr[j].fmt; j++)
    {
        if (arr[j].fmt == fmt[*i])
        {
            printed = arr[j].fn(list, buffer, flags, width, precision, size);
            return (printed);
        }
    }

    if (fmt[*i] == '%')
    {
        if (width > 0 && !(flags & F_MINUS))
        {
            if (flags & F_ZERO)
                write(1, "0", 1);
            while (--width > 0)
                write(1, " ", 1);
        }
        write(1, &fmt[*i], 1);
        if (width > 0 && (flags & F_MINUS))
        {
            while (--width > 0)
                write(1, " ", 1);
        }
        return (1);
    }
    return (-1);
}

/**
 * print_char - Prints a character
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_char(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    char c = va_arg(args, int);
    int printed = 0;

    if (width > 0 && !(flags & F_MINUS))
    {
        while (--width > 0)
            printed += handle_write_char(' ', buffer, flags, width, precision, size);
    }
    printed += handle_write_char(c, buffer, flags, width, precision, size);
    if (width > 0 && (flags & F_MINUS))
    {
        while (--width > 0)
            printed += handle_write_char(' ', buffer, flags, width, precision, size);
    }

    return (printed);
}

/**
 * print_string - Prints a string
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_string(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    char *str = va_arg(args, char *);
    int printed = 0;

    if (str == NULL)
        str = "(null)";

    if (precision >= 0)
        printed = print_string_with_precision(str, buffer, flags, width, precision, size);
    else
        printed = print_string_without_precision(str, buffer, flags, width, size);

    return (printed);
}

/**
 * print_int - Prints an integer
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_int(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    int n = va_arg(args, int);
    int is_positive = 1;

    if (n < 0)
    {
        is_positive = 0;
        n = -n;
    }

    return (write_number(is_positive, n, buffer, flags, width, precision, size));
}

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

