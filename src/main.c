/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:44:26 by mintan            #+#    #+#             */
/*   Updated: 2024/08/06 20:41:05 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/pipex.h"
#include "../include/libft.h"
#include "../include/ft_printf.h"

/* Description: XXXXX

*/

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex *pp;
	char	**paths;

	if (argc < 5)
		return (1);
	pp = init_pipex(argc - 3);
	init_files(pp, argv[1], argv[argc - 1]);
	paths = get_paths(envp);
	if (paths == NULL)
		free_pipex_empty(pp);
	init_cmd_paths(pp, argc, argv, paths);
	init_cmd_args(pp, argc, argv);
	exe_cmd(pp);
	free_ft_split(paths);
	free_pipex(pp);
}
