/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:26:42 by mintan            #+#    #+#             */
/*   Updated: 2024/06/09 11:47:29 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"
#include "../../include/libft.h"

/* Description: writes a character  */
int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

/* Description: Triggered when the input string contains a % format specifier.
   Calls other functions to handle the different format specifiers. */
static	int	format_chk(char c, va_list ptr)
{
	int	ret;

	ret = 0;
	if (c == 'c')
		ret += ft_putchar(va_arg(ptr, int));
	else if (c == 's')
		ret += ft_putstr(va_arg(ptr, char *));
	else if (c == 'p')
		ret += ft_putptr(va_arg(ptr, unsigned long), "0123456789abcdef");
	else if (c == 'd' || c == 'i')
		ret += ft_putnbr(va_arg(ptr, int));
	else if (c == 'u')
		ret += ft_putunsignednbr(va_arg(ptr, unsigned int));
	else if (c == 'x')
		ret += ft_puthexa(va_arg(ptr, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		ret += ft_puthexa(va_arg(ptr, unsigned int), "0123456789ABCDEF");
	else if (c == '%')
		ret += ft_putchar(c);
	return (ret);
}

/* Description: checks for format specifiers that are invalid. Returns a
   -1 if there are invalid format specifiers. */
static	int	checkspecifier(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == 'c' || str[i + 1] == 's')
				;
			else if (str[i + 1] == 'p')
				;
			else if (str[i + 1] == 'd' || str[i + 1] == 'i')
				;
			else if (str[i + 1] == 'u')
				;
			else if (str[i + 1] == 'x' || str[i +1] == 'X')
				;
			else if (str[i + 1] == '%')
				i++;
			else
				return (-1);
		}
		i++;
	}
	return (1);
}

/* Description: Attempts to replicate the real printf function. Handles the
   cspdiuxX% conversion:
   - %c: single character
   - %s: string
   - %p: void * pointer. Printed in hexadecimal format
   - %d: decimal (base 10) number
   - %i: same as %d
   - %u: unsigned decimal (base 10) number
   - %x: hexadecimal (base 16) lowercase
   - %X: hexadecimal (base 16) uppercase
   - %%: % sigm */
int	ft_printf(const char *str, ...)
{
	int		ret;
	int		i;
	va_list	ptr;

	ret = 0;
	i = 0;
	if (checkspecifier(str) == -1)
		return (-1);
	va_start(ptr, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			ret += format_chk(str[i + 1], ptr);
			i = i + 2;
		}
		else
		{
			ret += ft_putchar(str[i]);
			i++;
		}
	}
	va_end(ptr);
	return (ret);
}
