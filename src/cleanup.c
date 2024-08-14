/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 17:06:43 by mintan            #+#    #+#             */
/*   Updated: 2024/08/14 13:39:48 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include "../include/ft_printf.h"

/* Description: takes in the t_pipex structure and frees the memory allocated
   for each member systematically. This function is only used before the
   cmd_paths and cmd_args structure members are populated.
*/

void	free_pipex_empty(t_pipex *pp)
{
	free(pp->cmd_paths);
	free(pp->cmd_args);
	free(pp);
}

/* Description: frees memory allocated for members in an array of strings.
   Takes in an integer n: the number of elements in the string array.
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
	int	i;
	int	j;

	i = 0;
	while (i < n)
	{
		j = 0;
		while (arr[i][j] != NULL)
		{
			free(arr[i][j]);
			j++;
		}
		free (arr[i][j]);
		free (arr[i]);
		i++;
	}
}

/* Description: takes in the t_pipex structure and frees the memory allocated
   for each member systematically. This function is only used after the
   cmd_paths and cmd_args are populated.
*/

void	free_pipex(t_pipex *pp)
{
	free_astray(pp->cmd_args, pp->cmd_num);
	free_stray(pp->cmd_paths, pp->cmd_num);
	free_pipex_empty(pp);
}

/* Description: frees memory allocated for members in an array of strings
   generated from ft_split. The array of strings has NULL as the final member.
   Actions:
	1. Frees the memory allocated for each pointer in the string array (up
	   to the NULL member)
	2. Frees the memory allocated for the array
*/

void	free_ft_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr[i]);
	free(arr);
}
