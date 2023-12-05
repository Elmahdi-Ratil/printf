#include "main.h"

/*** WRITE HANDLE ***/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buff: Buffer array to handle print
 * @flg:  Calculates active flags.
 * @width: get width.
 * @pre: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buff[],
	int flg, int width, int pre, int size)
{ /* char is stored at left and paddind at buffer's right */
	int i = 0;
	char padd = ' ';

	UNUSED(pre);
	UNUSED(size);

	if (flg & F_ZERO)
		padd = '0';

	buff[i++] = c;
	buff[i] = '\0';

	if (width > 1)
	{
		buff[BUFF_SIZE - 1] = '\0';
		for (i = 0; i < width - 1; i++)
			buff[BUFF_SIZE - i - 2] = padd;

		if (flg & F_MINUS)
			return (write(1, &buff[0], 1) +
					write(1, &buff[BUFF_SIZE - i - 1], width - 1));
		else
			return (write(1, &buff[BUFF_SIZE - i - 1], width - 1) +
					write(1, &buff[0], 1));
	}

	return (write(1, &buff[0], 1));
}
/*** WRITE NUMBER ***/
/**
 * write_number - Prints a string
 * @is_negative: Lista of arguments
 * @ind: char types.
 * @buff: Buffer array to handle print
 * @flg:  Calculates active flags
 * @width: get width.
 * @pre: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buff[],
	int flg, int width, int pre, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flg & F_ZERO) && !(flg & F_MINUS))
		padd = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flg & F_PLUS)
		extra_ch = '+';
	else if (flg & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buff, flg, width, pre,
		length, padd, extra_ch));
}
/*** WRITE NUM ***/
/**
 * write_num - Write a number using a bufffer
 * @ind: Index at which the number starts on the buffer
 * @buff: Buffer
 * @flg: Flags
 * @width: width
 * @pre: Precision specifier
 * @length: Number length
 * @padd: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buff[],
	int flg, int width, int pre,
	int length, char padd, char extra_c)
{
	int i, padd_start = 1;

	if (pre == 0 && ind == BUFF_SIZE - 2 && buff[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (pre == 0 && ind == BUFF_SIZE - 2 && buff[ind] == '0')
		buff[ind] = padd = ' '; /* width is displayed with padding ' ' */
	if (pre > 0 && pre < length)
		padd = ' ';
	while (pre > length)
		buff[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (i = 1; i < width - length + 1; i++)
			buff[i] = padd;
		buff[i] = '\0';
		if (flg & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buff[--ind] = extra_c;
			return (write(1, &buff[ind], length) + write(1, &buff[1], i - 1));
		}
		else if (!(flg & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buff[--ind] = extra_c;
			return (write(1, &buff[1], i - 1) + write(1, &buff[ind], length));
		}
		else if (!(flg & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buff[--padd_start] = extra_c;
			return (write(1, &buff[padd_start], i - padd_start) +
				write(1, &buff[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buff[--ind] = extra_c;
	return (write(1, &buff[ind], length));
}
/*** WRITE UNSGND ***/
/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buff: Array of chars
 * @flg: Flags specifiers
 * @width: Width specifier
 * @pre: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char buff[],
	int flg, int width, int pre, int size)
{
	/* The number is stored at the bufer's right and starts at position i */
	int length = BUFF_SIZE - ind - 1, i = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (pre == 0 && ind == BUFF_SIZE - 2 && buff[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (pre > 0 && pre < length)
		padd = ' ';

	while (pre > length)
	{
		buff[--ind] = '0';
		length++;
	}

	if ((flg & F_ZERO) && !(flg & F_MINUS))
		padd = '0';

	if (width > length)
	{
		for (i = 0; i < width - length; i++)
			buff[i] = padd;

		buff[i] = '\0';

		if (flg & F_MINUS) /* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buff[ind], length) + write(1, &buff[0], i));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buff[0], i) + write(1, &buff[ind], length));
		}
	}

	return (write(1, &buff[ind], length));
}
/*** WRITE POINTER ***/
/**
 * write_pointer - Write a memory address
 * @buff: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Wwidth specifier
 * @flg: Flags specifier
 * @padd: Char representing the padding
 * @extra_c: Char representing extra char
 * @padd_start: Index at which padding should start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buff[], int ind, int length,
	int width, int flg, char padd, char extra_c, int padd_start)
{
	int i;

	if (width > length)
	{
		for (i = 3; i < width - length + 3; i++)
			buff[i] = padd;
		buff[i] = '\0';
		if (flg & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			buff[--ind] = 'x';
			buff[--ind] = '0';
			if (extra_c)
				buff[--ind] = extra_c;
			return (write(1, &buff[ind], length) + write(1, &buff[3], i - 3));
		}
		else if (!(flg & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buff[--ind] = 'x';
			buff[--ind] = '0';
			if (extra_c)
				buff[--ind] = extra_c;
			return (write(1, &buff[3], i - 3) + write(1, &buff[ind], length));
		}
		else if (!(flg & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buff[--padd_start] = extra_c;
			buff[1] = '0';
			buff[2] = 'x';
			return (write(1, &buff[padd_start], i - padd_start) +
				write(1, &buff[ind], length - (1 - padd_start) - 2));
		}
	}
	buff[--ind] = 'x';
	buff[--ind] = '0';
	if (extra_c)
		buff[--ind] = extra_c;
	return (write(1, &buff[ind], BUFF_SIZE - ind - 1));
}

