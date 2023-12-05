#include "main.h"

void print_buff(char buff[], int *buff_ind);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flg, width, pre, size, buff_ind = 0;
	va_list list;
	char buff[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buff[buff_ind++] = format[i];
			if (buff_ind == BUFF_SIZE)
				print_buff(buff, &buff_ind);
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buff(buff, &buff_ind);
			flg = get_flags(format, &i);
			width = get_width(format, &i, list);
			pre = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			printed = handle_print(format, &i, list, buff,
				flg, width, pre, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	print_buff(buff, &buff_ind);

	va_end(list);

	return (printed_chars);
}

/**
 * print_buff - Prints the contents of the buffer if it exist
 * @buff: Array of chars
 * @buff_ind: Index at which to add next char, represents the length.
 */
void print_buff(char buff[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buff[0], *buff_ind);

	*buff_ind = 0;
}

