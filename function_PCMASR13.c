#include "main.h"

/*** PRINT NON PRINTABLE ***/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buff: Buffer array to handle print
 * @flg:  Calculates active flags
 * @width: get width
 * @pre: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buff[],
	int flg, int width, int pre, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flg);
	UNUSED(width);
	UNUSED(pre);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buff[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buff, i + offset);

		i++;
	}

	buff[i + offset] = '\0';

	return (write(1, buff, i + offset));
}

/*** PRINT POINTER ***/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buff: Buffer array to handle print
 * @flg:  Calculates active flags
 * @width: get width
 * @pre: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buff[],
	int flg, int width, int pre, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buff[BUFF_SIZE - 1] = '\0';
	UNUSED(pre);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buff[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flg & F_ZERO) && !(flg & F_MINUS))
		padd = '0';
	if (flg & F_PLUS)
		extra_c = '+', length++;
	else if (flg & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buff, ind, length,
		width, flg, padd, extra_c, padd_start));
}


