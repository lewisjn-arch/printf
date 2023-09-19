#include "main.h"

/**
 * write_pointer - Writes a pointer to the buffer
 * @prefix: The prefix to print before the pointer
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters written
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
 * write_hexa - Writes an integer as a hexadecimal string to the buffer
 * @n: The integer to write
 * @map_to: The character map to use (lowercase or uppercase)
 * @buffer: Array of characters
 * @flags: Flags
 * @width: Width
 * @precision: Precision
 * @size: Size
 * Return: Number of characters written
 */
int write_hexa(unsigned int n, char map_to[], char buffer[], int flags, int width, int precision, int size)
{
    int num_len, printed = 0;
    char num[12];

    num_len = int_to_hexa(n, num, map_to);
    if (width > 0 && !(flags & F_MINUS) && !(flags & F_ZERO))
        printed += handle_write_string(' ', buffer, flags, width - MAX(precision, num_len), size);
    if (precision > 0)
        printed += handle_write_string('0', buffer, flags, precision - num_len, size);
    printed += handle_write_strnum(num, buffer, size, num_len);
    if (width > 0 && (flags & F_MINUS))
        printed += handle_write_string(' ', buffer, flags, width - MAX(precision, num_len), size);
    return (printed);
}

/**
 * int_to_str - Converts an integer to a string
 * @n: The integer to convert
 * @str: The resulting string
 * Return: Length of the string
 */
int int_to_str(int n, char str[])
{
    int i, sign;
    char temp;

    if ((sign = n) < 0)
        n = -n;

    i = 0;
    do
    {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        str[i++] = '-';
    str[i] = '\0';

    reverse_string(str);

    return (i);
}

/**
 * reverse_string - Reverses a string
 * @str: The string to reverse
 */
void reverse_string(char str[])
{
    int start = 0;
    int end = strlen(str) - 1;
    char temp;

    while (start < end)
    {
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}

