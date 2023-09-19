#include "main.h"

/**
 * write_number - Writes an integer to the buffer
 * @is_positive: 1 if the number is positive, 0 if negative
 * @n: The integer to print
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int write_number(int is_positive, int n, char buffer[], int flags, int width, int precision, int size)
{
    int num_len, printed = 0;
    char num[12];

    if (n == 0 && precision == 0)
        return (handle_write_number(buffer, flags, width, size));
    num_len = int_to_str(n, num);
    if (is_positive && (flags & F_PLUS))
        printed += handle_write_char('+', buffer, flags, size);
    else if (is_positive && (flags & F_SPACE))
        printed += handle_write_char(' ', buffer, flags, size);
    if (!is_positive && (flags & F_MINUS))
        printed += handle_write_char('-', buffer, flags, size);
    if (width > 0 && !(flags & F_MINUS) && !(flags & F_ZERO))
        printed += handle_write_string(' ', buffer, flags, width - MAX(precision, num_len), size);
    if (!is_positive && !(flags & F_MINUS) && (flags & F_ZERO))
        printed += handle_write_char('-', buffer, flags, size);
    if (precision > 0)
        printed += handle_write_string('0', buffer, flags, precision - num_len, size);
    printed += handle_write_string('0', buffer, flags, size - num_len, size);
    printed += handle_write_strnum(num, buffer, size, num_len);
    if (width > 0 && (flags & F_MINUS))
        printed += handle_write_string(' ', buffer, flags, width - MAX(precision, num_len), size);
    return (printed);
}

/**
 * write_pointer - Writes a pointer to the buffer
 * @prefix: The prefix to print before the pointer
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters printed
 */
int write_pointer(char *prefix, char buffer[], int flags, int width, int precision, int size)
{
    int printed = 0;

    if (width > 0 && !(flags & F_MINUS) && !(flags & F_ZERO))
        printed += handle_write_string(' ', buffer, flags, width - MAX(precision, 2), size);
    printed += handle_write_strnum(prefix, buffer, size, 2);
    if (width > 0 && (flags & F_MINUS))
        printed += handle_write_string(' ', buffer, flags, width - MAX(precision, 2), size);
    return (printed);
}

/**
 * handle_write_char - Writes a character to the buffer
 * @c: The character to write
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters written
 */
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size)
{
    if (width > 0 && !(flags & F_MINUS) && !(flags & F_ZERO))
        return (handle_write_string(' ', buffer, flags, width - 1, size) + handle_write_buffer_char(c, buffer, size));
    if (width > 0 && (flags & F_MINUS))
        return (handle_write_buffer_char(c, buffer, size) + handle_write_string(' ', buffer, flags, width - 1, size));
    return (handle_write_buffer_char(c, buffer, size));
}

/**
 * handle_write_number - Writes a number to the buffer
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @size: Size
 * Return: Number of characters written
 */
int handle_write_number(char buffer[], int flags, int width, int size)
{
    if (width > 0 && !(flags & F_MINUS) && !(flags & F_ZERO))
        return (handle_write_string(' ', buffer, flags, width - 1, size) + handle_write_buffer_char('0', buffer, size));
    if (width > 0 && (flags & F_MINUS))
        return (handle_write_buffer_char('0', buffer, size) + handle_write_string(' ', buffer, flags, width - 1, size));
    return (handle_write_buffer_char('0', buffer, size));
}

/**
 * handle_write_string - Writes a character multiple times to the buffer
 * @c: The character to write
 * @buffer: Array of characters
 * @flags: Flags
 * @count: Number of times to write the character
 * @size: Size
 * Return: Number of characters written
 */
int handle_write_string(char c, char buffer[], int flags, int count, int size)
{
    int i, printed = 0;

    for (i = 0; i < count; i++)
        printed += handle_write_buffer_char(c, buffer, size);

    return (printed);
}

