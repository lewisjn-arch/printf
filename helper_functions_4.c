#include "main.h"

/**
 * int_to_hexa - Converts an integer to a hexadecimal string
 * @n: The integer to convert
 * @str: The resulting string
 * @map_to: The character map to use (lowercase or uppercase)
 * Return: Length of the string
 */
int int_to_hexa(unsigned int n, char str[], char map_to[])
{
    int i = 0;
    unsigned int temp;

    if (n == 0)
    {
        str[i++] = '0';
    }
    else
    {
        while (n != 0)
        {
            temp = n % 16;
            str[i++] = map_to[temp];
            n /= 16;
        }
    }

    str[i] = '\0';
    reverse_string(str);

    return (i);
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

