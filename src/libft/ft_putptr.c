/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:26:42 by mintan            #+#    #+#             */
/*   Updated: 2024/06/08 21:05:51 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"
#include "../../include/libft.h"

/* Description: takes in the hexadecimal base, an unsigned long, and converts 
   it into a hexadecimal. Increments the value stored in the address of the 
   count and returns it.  */

static	void	ft_putunsignedlonghexa(unsigned long l, int *count, char *base)
{
	if (l > 15)
	{
		ft_putunsignedlonghexa(l / 16, count, base);
		ft_putunsignedlonghexa(l % 16, count, base);
	}
	else
	{
		ft_putchar(base[l]);
		(*count)++;
	}
}

/* Description: takes in a pointer as an unsigned long and writes it out as
   a hexadecimal string. Returns the length of the string. */

int	ft_putptr(unsigned long l, char *base)
{
	int		ret;

	ret = 0;
	if (l == 0)
	{
		ret = write(1, "(nil)", 5);
	}
	else
	{
		ret = write(1, "0x", 2);
		ft_putunsignedlonghexa(l, &ret, base);
	}
	return (ret);
}
