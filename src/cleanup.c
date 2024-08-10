/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:06:43 by mintan            #+#    #+#             */
/*   Updated: 2024/08/10 17:26:06 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include "../include/ft_printf.h"


/* Description: takes in the t_pipex structure and frees the memory allocated
   for each member systematically.

*/

void	free_pipex(t_pipex *pp)
{

}



/* Description: frees memory allocated for an array of strings. Takes in
   an integer n: the number of elements in the string array.
*/

void	free_stray(char **arr, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(arr[i]);
		i++;
	}
}

/* Description: frees memory allocated for an array of array of strings.
   Takes in an integer n: the number of string arrays in the array. Each array
   of strings should have NULL as the last member of the array.
*/

void	free_astray(char ***arr, int n)
{
	
}
