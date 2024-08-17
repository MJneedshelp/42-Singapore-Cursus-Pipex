/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:57:57 by mintan            #+#    #+#             */
/*   Updated: 2024/08/17 12:21:23 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include "../include/ft_printf.h"

char	*get_cmd(char *full_cmd)
{
	char	**split;
	char	*cmd;

	split = ft_split(full_cmd, ' ');
	if (split == NULL)
		return (NULL);
	cmd = ft_strdup(split[0]);
	free_ft_split(split);
	return (cmd);
}

/* Description: generates a cmd path based on the full command and the paths
   passed in.
   Inputs:
	1. full_cmd: a string in *argv[]. E.g.: "ls -l"
	2. an array of paths. E.g.: ["/usr/bin", "usr/sbin"]
   Actions:
	1. Retrieves the command in full_cmd by using ft_split[0]
	2. For each command, combine with each path from **paths and check if the
	   combined filepath is executable.
	   - If executable, ft_strdup into the cmd_paths if execuable
	   - If there are no executable paths, add the command as it is into
	   cmd_paths
	3. If any of the malloc fails, free previously allocated memory and
	   return NULL
*/
char	*get_cmd_path(char *full_cmd, char **paths)
{
	char	*cmd;
	char	*cmd_path;
	int		i;

	i = 0;
	cmd = get_cmd(full_cmd);
	if (cmd == NULL)
		return (NULL);
	if (access(cmd, X_OK) == 0)
		return (cmd);
	if (paths != NULL)
	{
		while (paths[i] != NULL)
		{
			cmd_path = ft_pathjoin(paths[i], cmd);
			if (cmd_path == NULL)
				return (free(cmd), NULL);
			if (access(cmd_path, X_OK) == 0)
				return (free(cmd), cmd_path);
			i++;
			free (cmd_path);
		}
	}
	ft_printf("%s: command not found\n", cmd);
	return (cmd);
}

/* Description: populates the pp->cmd_paths in the t_pipex struct
   Actions:
	1. Retrieves the command path in the argv[] using ft_split
		- starts from argv[2] if there is no here_doc
		- starts from argv[3] if there is here_doc
	2. str_dup each command path in to pp->cmd_paths
	3. If any of the malloc fails, set cmd paths as NULL and return
*/
void	init_cmd_paths(t_pipex *pp, int argc, char *argv[], char **paths)
{
	int		i;
	int		j;

	if (pp->here_doc_path == NULL)
		i = 2;
	else
		i = 3;
	j = 0;
	while (i < argc - 1)
	{
		pp->cmd_paths[j] = get_cmd_path(argv[i], paths);
		if (pp->cmd_paths[j] == NULL)
		{
			free_stray(pp->cmd_paths, j);
			free_pipex_empty(pp);
			exit(EXIT_FAILURE);
		}
		i++;
		j++;
	}
}

/* Description: populates the pp->cmd_args in the t_pipex struct
   Actions:
	1. Retrieves the command arguments in the argv[] using ft_split
		- starts from argv[2] if there is no here_doc
		- starts from argv[3] if there is here_doc
	2. If any of the malloc fails, set cmd args as NULL and return
*/
void	init_cmd_args(t_pipex *pp, int argc, char *argv[])
{
	char	**cmd_arg;
	int		i;
	int		j;

	if (pp->here_doc_path == NULL)
		i = 2;
	else
		i = 3;
	j = 0;
	while (i < argc - 1)
	{
		cmd_arg = ft_split(argv[i], ' ');
		pp->cmd_args[j] = cmd_arg;
		if (cmd_arg == NULL)
		{
			free_astray(pp->cmd_args, j);
			free_stray(pp->cmd_paths, pp->cmd_num);
			free_pipex_empty(pp);
			exit(EXIT_FAILURE);
		}
		i++;
		j++;
	}
}
