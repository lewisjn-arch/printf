#include "main.h"

/**
 * extract_flags - This function calculates active flags
 * @format: String in which to print the arguments
 * @i: take a parameter pointer to an integer.
 * Return: active flags
 */
int extract_flags(const char *format, int *i)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int j, current_index;
	int flags = 0;
	const char FLAGS_CHAR[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {FLAGS_MINUS, FLAGS_PLUS, FLAGS_ZERO,
		FLAGS_HASH, FLAGS_SPACE, 0};

	for (current_index = *i + 1; format[current_index] != '\0'; current_index++)
	{
		for (j = 0; FLAGS_CHAR[j] != '\0'; j++)
			if (format[current_index] == FLAGS_CHAR[j])
			{
				flags |= FLAGS_ARR[j];
				break;
			}

		if (FLAGS_CHAR[j] == 0)
			break;
	}

	*i = current_index - 1;

	return (flags);
}
