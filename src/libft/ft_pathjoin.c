/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pathjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:48:03 by mintan            #+#    #+#             */
/*   Updated: 2024/05/23 13:53:28 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

/* Description: Allocates with malloc(3) and returns a combined path.
   Joins 's1' and 's2' with a '\'
   - s1: prefix
   - s2: suffix
*/

char	*ft_pathjoin(char const *s1, char const *s2)
{
	char	*ptr;

	ptr = ft_strjoin(s1, "/");
	if (ptr == NULL)
		return (NULL);
	ptr = ft_strjoin(ptr, s2);
	return (ptr);
}
