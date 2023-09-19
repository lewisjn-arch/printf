#include "main.h"

/**
 * char_print - Prints a character.
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
    char c = (char)va_arg(args, int);
    int i = 0;

    UNUSED(flags);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    buffer[i++] = c;
    buffer[i] = '\0';

    return (write(1, &c, 1));
}

/**
 * string_print - Prints a string.
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed
 */
int string_print(va_list args, char buffer[], int flags,
                int width, int precision, int size)
{
    char *str = va_arg(args, char *);
    int i = 0;

    UNUSED(flags);
    UNUSED(width);

    if (str == NULL)
        str = "(null)";

    if (precision < 0)
        precision = _strlen(str);

    while (str[i] != '\0' && (i < precision || precision == -1))
    {
        buffer[i] = str[i];
        i++;
    }

    buffer[i] = '\0';

    return (write(1, buffer, i));
}

/**
 * percentage_print - Prints a percentage sign.
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
    char percent = '%';

    UNUSED(args);
    UNUSED(width);
    UNUSED(precision);
    UNUSED(size);

    if (flags & F_MINUS)
    {
        write(1, &percent, 1);
        width--;
        while (width > 0)
        {
            write(1, " ", 1);
            width--;
        }
    }
    else
    {
        while (width > 1)
        {
            write(1, " ", 1);
            width--;
        }
        write(1, &percent, 1);
    }

    return (1);
}

/**
 * integer_print - Prints an integer.
 * @args: List of arguments
 * @buffer: Buffer array for printing
 * @flags: Active flags
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 * Return: Number of characters printed.
 */
int integer_print(va_list args, char buffer[], int flags,
                 int width, int precision, int size)
{
    int num = va_arg(args, int);
    int i = 0, negative = 0;
    char padd = ' ', extra_char = 0;

    UNUSED(size);

    if (num < 0)
        negative = 1;

    if ((flags & F_ZERO) && !(flags & F_MINUS))
        padd = '0';

    if (negative)
        extra_char = '-';
    else if (flags & F_PLUS)
        extra_char = '+';
    else if (flags & F_SPACE)
        extra_char = ' ';

    i += itoa(num, &buffer[i]);

    return (number_write(negative, i, buffer, flags, width, precision, size));
}

