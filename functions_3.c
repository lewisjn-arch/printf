#include "main.h"

/**
 * print_pointer - Prints a pointer address
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_pointer(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    unsigned long int p = (unsigned long int)va_arg(args, void *);

    if (p == 0)
        return (write_pointer("(nil)", buffer, flags, width, precision, size));
    return (write_pointer("0x", buffer, flags, width, precision, size) +
            write_number(1, p, buffer, flags | F_HASH, width, precision, size));
}

/**
 * print_reverse - Prints a string in reverse
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_reverse(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    char *str = va_arg(args, char *);
    int printed = 0;

    if (str == NULL)
        str = ")llun(";
    while (*str)
    {
        printed += handle_write_char(*str, buffer, flags, size);
        str++;
    }

    return (printed);
}

/**
 * print_rot13string - Prints a string using rot13 encoding
 * @args: Argument list
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int print_rot13string(va_list args, char buffer[], int flags, int width, int precision, int size)
{
    char *str = va_arg(args, char *);
    int i, printed = 0;
    char c;

    if (str == NULL)
        str = "(null)";
    for (i = 0; str[i]; i++)
    {
        c = str[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        {
            if ((c >= 'a' && c <= 'm') || (c >= 'A' && c <= 'M'))
                c += 13;
            else
                c -= 13;
        }
        printed += handle_write_char(c, buffer, flags, size);
    }

    return (printed);
}

