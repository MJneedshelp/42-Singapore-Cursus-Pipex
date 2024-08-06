/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_least.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:28:41 by mintan            #+#    #+#             */
/*   Updated: 2024/05/14 19:38:35 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/* Description: Takes in 2 integers and returns the smaller integer. Returns
   the integer value if both integers are the same size
*/

int	ft_least(int int1, int int2, int int3)
{
	if (int1 <= int2 && int1 <= int3)
		return (int1);
	if (int2 <= int1 && int2 <= int3)
		return (int2);
	else
		return (int3);
}
