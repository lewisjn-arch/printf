#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdbool.h>
#include "main.h"

/**
 * print_binary - Prints an unsigned integer in binary format.
 * @num: The unsigned integer to be printed in binary.
 */
void print_binary(unsigned int num) {
    if (num / 2 != 0) {
        print_binary(num / 2);
    }
    putchar('0' + (num % 2));
}

/**
 * _printf - Custom printf function that handles various conversion specifiers.
 * @fmt: A format string containing zero or more conversion specifiers.
 *
 * Return: (int) The number of characters printed (excluding the null byte used
 * to end output to strings).
 */
int _printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    int count = 0;

    char buffer[1024];
    int buf_idx = 0;

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            switch (*fmt) {
                case 'c':
                    buffer[buf_idx++] = va_arg(args, int);
                    count++;
                    break;
                case 's':
                    while (buf_idx < 1023 && (buffer[buf_idx++] = *va_arg(args, char *)))
                        count++;
                    break;
                case 'd':
                case 'i':
                    buf_idx += snprintf(buffer + buf_idx, 1023 - buf_idx, "%d", va_arg(args, int));
                    count++;
                    break;
                case 'u':
                    buf_idx += snprintf(buffer + buf_idx, 1023 - buf_idx, "%u", va_arg(args, unsigned int));
                    count++;
                    break;
                case 'o':
                    buf_idx += snprintf(buffer + buf_idx, 1023 - buf_idx, "%o", va_arg(args, unsigned int));
                    count++;
                    break;
                case 'x':
                    buf_idx += snprintf(buffer + buf_idx, 1023 - buf_idx, "%x", va_arg(args, unsigned int));
                    count++;
                    break;
                case 'X':
                    buf_idx += snprintf(buffer + buf_idx, 1023 - buf_idx, "%X", va_arg(args, unsigned int));
                    count++;
                    break;
                case 'S': {
                    char *s = va_arg(args, char *);
                    while (*s) {
                        if ((*s >= 1 && *s <= 31) || *s >= 127) {
                            buf_idx += snprintf(buffer + buf_idx, 1023 - buf_idx, "\\x%02X", (unsigned char)*s);
                            count += 4;
                        } else {
                            buffer[buf_idx++] = *s;
                            count++;
                        }
                        s++;
                    }
                    break;
                }
                case 'p': {
                    void *ptr = va_arg(args, void *);
                    buf_idx += snprintf(buffer + buf_idx, 1023 - buf_idx, "0x%lx", (unsigned long)ptr);
                    count += 2;
                    break;
                }
                case '%':
                    buffer[buf_idx++] = '%';
                    count++;
                    break;
                default:
                    buffer[buf_idx++] = '%';
                    count++;
                    break;
            }
        } else {
            buffer[buf_idx++] = *fmt;
            count++;
        }

        if (buf_idx >= 1023) {
            buffer[buf_idx] = '\0';
            write(1, buffer, buf_idx);
            buf_idx = 0;
        }

        fmt++;
    }

    if (buf_idx > 0) {
        buffer[buf_idx] = '\0';
        write(1, buffer, buf_idx);
    }

    va_end(args);

    return (count);
}
