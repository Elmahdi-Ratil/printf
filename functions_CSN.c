#include "main.h"

/*** PRINT CHAR ***/
/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buff: Buffer array to handle print
 * @flg:  Calculates active flags
 * @width: Width
 * @pre: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buff[],
	int flg, int width, int pre, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buff, flg, width, pre, size));
}
