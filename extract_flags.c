#include "main.h"

/**
 * extract_flags - Extract and evaluate flags
 * @format: Formatted string to print arguments.
 * @i: Pointer to track the current format position.
 *
 * Return: Flags value based on the format specifier.
 */
int extract_flags(const char *format, int *i)
{
    int current_index = *i + 1;
    int flags = 0;

    while (format[current_index] == '-' || format[current_index] == '+'
           || format[current_index] == ' ' || format[current_index] == '#'
           || format[current_index] == '0')
    {
        if (format[current_index] == '-')
            flags |= F_MINUS;
        else if (format[current_index] == '+')
            flags |= F_PLUS;
        else if (format[current_index] == ' ')
            flags |= F_SPACE;
        else if (format[current_index] == '#')
            flags |= F_HASH;
        else if (format[current_index] == '0')
            flags |= F_ZERO;

        current_index++;
    }

    *i = current_index - 1;

    return (flags);
}

