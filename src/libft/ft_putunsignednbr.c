/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsignednbr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:26:42 by mintan            #+#    #+#             */
/*   Updated: 2024/06/08 21:04:12 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"
#include "../../include/libft.h"

/* Description: converts an unsigned integer into a string and
   writes the string. Returns the string length */

int	ft_putunsignednbr(unsigned int n)
{
	int		ret;
	long	l;

	ret = 0;
	l = (long)n;
	ft_putlongnbr(l, &ret);
	return (ret);
}
