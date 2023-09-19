#include "main.h"

/**
 * print_handler - Processes and prints an argument based on its type.
 * @format: Formatted string containing the arguments and format specifiers.
 * @index: Index for tracking the current position in the format string
 * @args: A list of arguments to be printed.
 * @buffer: Buffer array to hold the printed characters
 * @flags: Flags that control the printing format
 * @width: Width specification for formatting
 * @precision: Precision specification for formatting.
 * @size: Size specifier for formatting.
 *
 * Return: The number of characters printed or -1 on failure.
 */
int print_handler(const char *format, int *index, va_list args, char buffer[],
                  int flags, int width, int precision, int size)
{
    int i, unknown_length = 0, printed_characters = -1;
    fmt_t fmt_types[] = {
        {'c', char_print}, {'s', string_print}, {'%', percentage_print},
        {'i', integer_print}, {'d', integer_print}, {'b', binary_print},
        {'u', unsigned_print}, {'o', octal_print}, {'x', hexadecimal_print},
        {'X', print_upper_hexa}, {'p', pointer_print}, {'S', non_printable_print},
        {'r', reverse_print}, {'R', rot13string_print}, {'\0', NULL}
    };

    for (i = 0; fmt_types[i].format != '\0'; i++)
    {
        if (format[*index] == fmt_types[i].format)
        {
            return (fmt_types[i].fn(args, buffer, flags, width, precision, size));
        }
    }

    if (fmt_types[i].format == '\0')
    {
        if (format[*index] == '\0')
            return (-1);
        unknown_length += write(1, "%%", 1);
        if (format[*index - 1] == ' ')
            unknown_length += write(1, " ", 1);
        else if (width)
        {
            --(*index);
            while (format[*index] != ' ' && format[*index] != '%')
                --(*index);
            if (format[*index] == ' ')
                --(*index);
            return (1);
        }
        unknown_length += write(1, &format[*index], 1);
        return (unknown_length);
    }
    return (printed_characters);
}

