/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_infile_random.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 05:12:22 by mintan            #+#    #+#             */
/*   Updated: 2024/08/20 05:12:22 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include "../include/ft_printf.h"
#include "../include/get_next_line.h"

void	check_infile_random(t_pipex *pp, char *infile)
{
	if (ft_strncmp(infile, "/dev/random", 11) == 0 && ft_strlen(infile) == 11)
		pp->infile_random = 1;
	if (ft_strncmp(infile, "/dev/urandom", 12) == 0 && ft_strlen(infile) == 12)
		pp->infile_random = 1;
}
