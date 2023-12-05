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
