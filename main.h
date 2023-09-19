#ifndef MAIN_H
#define MAIN_H

#include <limits.h>
#include <stddef.h>
#include <stdarg.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define MAX_BUFFER_SIZE 1024

/**
 * struct format_specifier - Format specifier for custom_printf
 * @specifier: The format specifier (e.g., 'c', 's', 'd', etc.)
 * @print_func: The function pointer to the corresponding print function
 */
typedef struct format_specifier
{
    char specifier;
    int (*print_func)(va_list args, char buffer[], int flags, int width, int precision, int size);
} format_specifier_t;

/**
 * struct print_flag - Print flag
 * @flag: The flag character (e.g., '-', '+', etc.)
 * @value: The flag value (0 or 1)
 */
typedef struct print_flag
{
    char flag;
    int value;
} print_flag_t;

/**
 * struct print_state - Print state
 * @buffer: The output buffer
 * @buffer_size: The size of the buffer
 * @printed_chars: The number of characters printed
 * @flags: The flags (e.g., '-', '0', etc.)
 * @width: The width specifier
 * @precision: The precision specifier
 * @size: The length specifier (e.g., 'h', 'l', etc.)
 */
typedef struct print_state
{
    char buffer[MAX_BUFFER_SIZE];
    int buffer_size;
    int printed_chars;
    print_flag_t flags[5];
    int width;
    int precision;
    char size;
} print_state_t;

/**
 * struct format_func - Format function for custom_printf
 * @specifier: The format specifier (e.g., 'c', 's', 'd', etc.)
 * @func: The function pointer to the corresponding print function
 * @next: The pointer to the next format function
 */
typedef struct format_func
{
    char specifier;
    int (*func)(print_state_t *, va_list);
    struct format_func *next;
} format_func_t;

/**
 * enum format_length - Format length for custom_printf
 * @LENGTH_NONE: No length modifier
 * @LENGTH_HH: hh length modifier
 * @LENGTH_H: h length modifier
 * @LENGTH_L: l length modifier
 * @LENGTH_LL: ll length modifier
 * @LENGTH_Z: z length modifier
 * @LENGTH_J: j length modifier
 * @LENGTH_T: t length modifier
 * @LENGTH_BIG_L: L length modifier
 */
typedef enum format_length
{
    LENGTH_NONE,
    LENGTH_HH,
    LENGTH_H,
    LENGTH_L,
    LENGTH_LL,
    LENGTH_Z,
    LENGTH_J,
    LENGTH_T,
    LENGTH_BIG_L
} format_length_t;

/**
 * struct format_info - Format information for custom_printf
 * @specifier: The format specifier (e.g., 'c', 's', 'd', etc.)
 * @length: The length modifier (e.g., 'h', 'l', etc.)
 */
typedef struct format_info
{
    char specifier;
    format_length_t length;
} format_info_t;

/**
 * struct format_token - Format token for custom_printf
 * @start: The start position of the token
 * @end: The end position of the token
 * @info: The format information for the token
 */
typedef struct format_token
{
    const char *start;
    const char *end;
    format_info_t info;
} format_token_t;

/**
 * struct custom_printf_info - Custom printf information
 * @format_funcs: The format functions
 * @buffer: The output buffer
 * @buffer_size: The size of the buffer
 * @printed_chars: The number of characters printed
 * @format_tokens: The format tokens
 * @format_token_count: The number of format tokens
 */
typedef struct custom_printf_info
{
    format_func_t *format_funcs;
    char *buffer;
    size_t buffer_size;
    int printed_chars;
    format_token_t *format_tokens;
    size_t format_token_count;
} custom_printf_info_t;

int _printf(const char *format, ...);

/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16

/* SIZES */
#define S_LONG 2
#define S_SHORT 1

struct fmt
{
    char fmt;
    int (*fn)(va_list, char[], int, int, int, int);
};

typedef struct fmt fmt_t;

int custom_printf(const char *format, ...);
int handle_print(const char *fmt, int *i, va_list list, char buffer[], int flags, int width, int precision, int size);

/* Functions for printing characters and strings */
int print_char(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_string(va_list args, char buffer[], int flags, int width, int precision, int size);

/* Functions for printing numbers */
int print_int(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_binary(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_unsigned(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_octal(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_hexadecimal(va_list args, char buffer[], int flags, int width, int precision, int size);
int print_hexa_upper(va_list args, char buffer[], int flags, int width, int precision, int size);

int print_hexa(va_list args, char map_to[], char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Function for printing non-printable characters */
int print_non_printable(va_list args, char buffer[], int flags, int width, int precision, int size);

/* Function for printing memory addresses */
int print_pointer(va_list args, char buffer[], int flags, int width, int precision, int size);

/* Functions for handling other specifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list args);
int get_precision(const char *format, int *i, va_list args);
int get_size(const char *format, int *i);

/* Function for printing strings in reverse */
int print_reverse(va_list args, char buffer[], int flags, int width, int precision, int size);

/* Function for printing a string in ROT13 */
int print_rot13string(va_list args, char buffer[], int flags, int width, int precision, int size);

/* Width handling functions */
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[], int flags, int width, int precision, int size);
int write_num(int ind, char buffer[], char *num, int len);

#endif /* MAIN_H */

