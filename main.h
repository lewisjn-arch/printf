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

int _printf(const char *format, ...);
<<<<<<< HEAD
int print_handler(const char *format, int *i,
		va_list args, char buffer[], int flags,
		int width, int precision, int size);

/****************** FUNCTIONS ******************/

/* Functions to print chars and strings */
int char_print(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int string_print(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int percentage_print(va_list args, char buffer[],
		int flags, int width, int precision, int size);

/* Functions to print numbers */
int integer_print(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int binary_print(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int unsigned_print(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int octal_print(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int hexadecimal_print(va_list args, char buffer[],
		int flags, int width, int precision, int size);
int print_upper_hexa(va_list args, char buffer[],
		int flags, int width, int precision, int size);

int hexa_print(va_list args, char map[],
		char buffer[], int flags, char flag_ch,
		int width, int precision, int size);

/* Function to print non-printable characters */
int non_printable(va_list args, char buffer[],
		int flags, int width, int precision, int size);

/* Function to print memory address */
int pointer_print(va_list args, char buffer[],
		int flags, int width, int precision, int size);

/* Functions to handle other specifiers */
int extract_flags(const char *format, int *i);
int extract_width(const char *format, int *i, va_list args);
int extract_precision(const char *format, int *i, va_list args);
int extract_size(const char *format, int *i);

/* Function to print string in reverse */
int reverse_print(va_list args, char buffer[],
		int flags, int width, int precision, int size);

/* Function to print a string in rot13 */
int rot13string_print(va_list args, char buffer[],
		int flags, int width, int precision, int size);

/* Width handler */
int handle_character_write(char c, char buffer[],
		int flags, int width, int precision, int size);
int number_write(int is_positive, int index, char buffer[],
		int flags, int width, int precision, int size);
int num_write(int i, char bff[], int flags, int width, int precise,
		int length, char padd, char extra_char);
int pointer_write(char buffer[], int index, int length,
		int width, int flags, char padd, char extra_char, int padd_start);

int unsigned_write(int negative, int index,
		char buffer[]i,
		int flags, int width, int precision, int size);
=======
int handle_print(const char *fmt, int *i,
va_list list, char buffer[], int flags, int width, int precision, int size);

/****************** FUNCTIONS ******************/

/* Funtions to print chars and strings */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Functions to print numbers */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size);

int print_hexa(va_list types, char map_to[],
char buffer[], int flags, char flag_ch, int width, int precision, int size);

/* Function to print non printable characters */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Funcion to print memory address */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* Funciotns to handle other specifiers */
int get_flags(const char *format, int *i);
int get_width(const char *format, int *i, va_list list);
int get_precision(const char *format, int *i, va_list list);
int get_size(const char *format, int *i);

/*Function to print string in reverse*/
int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/*Function to print a string in rot 13*/
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size);

/* width handler */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size);
int write_number(int is_positive, int ind, char buffer[],
	int flags, int width, int precision, int size);
int write_num(int ind, char bff[], int flags, int width, int precision,
	int length, char padd, char extra_c);
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind,
char buffer[],
	int flags, int width, int precision, int size);
>>>>>>> e318d762c410e38a1726e2776fc79c6dca8e93e4

/****************** UTILS ******************/
int is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int size);
long int convert_size_unsgnd(unsigned long int num, int size);

#endif /* MAIN_H */

