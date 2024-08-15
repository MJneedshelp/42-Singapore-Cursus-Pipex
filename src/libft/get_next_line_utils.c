/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 11:08:04 by mintan            #+#    #+#             */
/*   Updated: 2024/07/01 21:25:30 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

/* Description: Calculates the length of a given string.Does not include the
   null character '\0'. */

size_t	gnl_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (str != NULL)
	{
		while (str[count] != '\0')
			count++;
	}
	return (count);
}

/* Description: copies n bytes from memory area src to memory area dest. Memory
   areas may overlap. Copying takes place as though the bytes are first copied
   into a temporary array that does not overlap src or dest. The bytes are
   then copied from the temporary array to dest. */

void	*gnl_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*x;
	unsigned char	*y;

	x = (unsigned char *)(dest);
	y = (unsigned char *)(src);
	if (x == y || n == 0)
		return (dest);
	if (dest < src)
	{
		while (n--)
			*(x++) = *(y++);
	}
	else
	{
		while (n--)
			x[n] = y[n];
	}
	return (dest);
}

/* Description: Allocates with malloc(3) and returns a substring from the
   string s. The substring begins at index 'start' and is of the maximum size
   'len'. */

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (len <= gnl_strlen(s) - start)
		ptr = (char *)malloc((len + 1) * sizeof(char));
	else
		ptr = (char *)malloc((gnl_strlen(s) - start + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	if (len <= gnl_strlen(s) - start)
	{
		gnl_memmove(ptr, (s + start), len);
		*(ptr + len) = '\0';
	}
	else
	{
		gnl_memmove(ptr, (s + start), gnl_strlen(s) - start);
		*(ptr + gnl_strlen(s) - start) = '\0';
	}
	return (ptr);
}

/* Description: Allocates with malloc(3) and returns a new string, which is
   the result of the concatenation of 's1' and 's2'. Frees 's1' and sets it
   to NULL.
   - s1: prefix
   - s2: suffix
   Frees 's1' and 's2' of malloc fails
*/

char	*gnl_strjoin(char **s1, char *s2)
{
	char	*ptr;
	size_t	len1;
	size_t	len2;

	len1 = gnl_strlen(*s1);
	len2 = gnl_strlen(s2);
	if (len1 == 0 && len2 == 0)
		return (NULL);
	ptr = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	gnl_memmove(ptr, *s1, len1);
	gnl_memmove(ptr + len1, s2, len2);
	*(ptr + len1 + len2) = '\0';
	freemem(s1, NULL);
	return (ptr);
}

/* Description: returns a pointer to a new string which is a duplicate of the
   string s. Memory for the new string is obtained with malloc and can be freed
   with free. */

char	*gnl_strdup(char **s)
{
	size_t	len;
	char	*ptr;
	size_t	i;

	i = 0;
	len = gnl_strlen(*s);
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (ptr == NULL)
		return (freemem(s, NULL), ptr);
	while ((*s)[i++] != '\0')
		ptr[i - 1] = (*s)[i - 1];
	ptr[i - 1] = '\0';
	freemem(s, NULL);
	return (ptr);
}
