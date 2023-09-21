#ifndef MAIN_H
#define MAIN_H
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024

/* FLAGS */
#define FLAGS_MINUS 1
#define FLAGS_PLUS 2
#define FLAGS_ZERO 4
#define FLAGS_HASH 8
#define FLAGS_SPACE 16

/* SIZES */
#define SIZE_LONG 2
#define SIZE_SHORT 1

/**
 * struct format - Struct op
 *
 * @format: The format.
 * @fn: The function associated.
 */
struct format
{
	char format;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
 * typedef struct format fmt_t - Struct op
 *
 * @format: The format.
 * @fmt_t: The function associated.
 */
typedef struct format fmt_t;

int extract_flags(const char *format, int *i);
int extract_precision(const char *format, int *i, va_list args);
int extract_width(const char *format, int *i, va_list args);
int extract_size(const char *format, int *i);
int char_print(va_list args, char buffer[], int flags,
		int width, int precision, int size);
int string_print(va_list args, char buffer[], int flags,
		int width, int precision, int size);
int percentage_print(va_list args, char buffer[], int flags,
		int width, int precision, int size);
int integer_print(va_list args, char buffer[], int flags,
		int width, int precision, int size);
int binary_print(va_list args, char buffer[], int flags,
		int width, int precision, int size);
int unsigned_print(va_list args, char buffer[], int flags,
		int width, int precision, int size);
int octal_print(va_list args, char buffer[], int flags,
		int width, int precision, int size);
int hexadecimal_print(va_list args, char buffer[], int flags,
		int width, int precision, int size);
int print_upper_hexa(va_list args, char buffer[], int flags,
		int width, int precision, int size);
int hexa_print(va_list args, char map_to[], char buffer[], int flags,
		char flag_char, int width, int precision, int size);
int pointer_print(va_list args, char buffer[], int flags, int width,
		int precision, int size);
int non_printable(va_list args, char buffer[], int flags, int width,
		int precision, int size);
int reverse_print(va_list args, char buffer[], int flags, int width,
		int precision, int size);
int rot13string_print(va_list args, char buffer[], int flags, int width,
		int precision, int size);
int handle_character_write(char s, char buffer[], int flags, int width,
		int precision, int size);
int number_write(int negative, int index, char buffer[], int flags, int width,
		int precision, int size);
int num_write(int index, char buffer[], int flags, int width, int prec,
		int length, char padd, char extra_char);
int unsigned_write(int negative, int index, char buffer[], int flags,
		int width, int precision, int size);
int pointer_write(char buffer[], int index, int length, int width, int flags,
		char padd, char extra_char, int padd_start);
int print_handler(const char *format, int *index, va_list args, char buffer[],
		int flags, int width, int precision, int size);
int printable(char c);
int append_hexacode(char ascii, char buffer[], int i);
int digit(char c);
long int convert_number_size(long int num, int size);
long int convert_unsigned_size(unsigned long int num, int size);
void print_buffer(char buffer[], int *b_index);
int _printf(const char *format, ...);

#endif /* MAIN_H */

