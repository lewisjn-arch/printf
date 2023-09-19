#include "main.h"

/**
 * digit - Check if a character is a digit.
 * @c: The character to check.
 *
 * Return: 1 if it's a digit, 0 otherwise.
 */
int digit(char c)
{
    return (c >= '0' && c <= '9');
}

/**
 * printable - Check if a character is printable.
 * @c: The character to check.
 *
 * Return: 1 if it's printable, 0 otherwise.
 */
int printable(char c)
{
    return (c >= 32 && c <= 126);
}

/**
 * itoa - Convert an integer to a string.
 * @n: The integer to convert.
 * @buffer: The buffer to store the result.
 *
 * Return: The length of the converted string.
 */
int itoa(int n, char buffer[])
{
    int i, sign;

    if ((sign = n) < 0)
        n = -n;
    i = 0;
    do
    {
        buffer[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);
    if (sign < 0)
        buffer[i++] = '-';
    buffer[i] = '\0';
    return (i);
}

/**
 * hex_itoa - Convert an unsigned integer to a hexadecimal string.
 * @n: The unsigned integer to convert.
 * @buffer: The buffer to store the result.
 *
 * Return: The length of the converted string.
 */
int hex_itoa(unsigned int n, char buffer[])
{
    int i;

    i = 0;
    do
    {
        buffer[i++] = "0123456789abcdef"[n % 16];
    } while ((n /= 16) > 0);
    buffer[i] = '\0';
    return (i);
}

