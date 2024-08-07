/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:57:57 by mintan            #+#    #+#             */
/*   Updated: 2024/08/06 20:39:37 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"

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
	char	**split;
	char	*cmd;
	char	*cmd_path;
	int		i;

	i = 0;
	split = ft_split(full_cmd, ' ');
	if (split == NULL)
		return (NULL);
	cmd = ft_strdup(split[0]);
	if (cmd == NULL)
		return (free(split), NULL);
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
	return (cmd);
}

/* Description: populates the pp->cmd_paths in the t_pipex struct
   Actions:
	1. Retrieves the command path in argv[1] to argv[n-1]. Use ft_split
	2. str_dup each command path in to pp->cmd_paths
	3. If any of the malloc fails, set cmd paths as NULL and return
*/
void	init_cmd_paths(t_pipex *pp, int argc, char *argv[], char **paths)
{
	char	*cmd_path;
	int		i;
	int		j;

	i = 2;
	j = 0;
	while (i < argc - 1)
	{
		cmd_path = get_cmd_path(argv[i], paths);
		if (cmd_path == NULL)
		{
			//probably needs a function here to clean up all the previous pp->cmd path mallocs
			pp->cmd_paths = NULL;
			return;
		}
		pp->cmd_paths[j] = ft_strdup(cmd_path);
		free (cmd_path);
		if (pp->cmd_paths[j] == NULL)
		{
			//probably needs a function here to clean up all the previous pp->cmd path mallocs
			pp->cmd_paths = NULL;
			return;
		}
		i++;
		j++;
	}
}

/* Description: populates the pp->cmd_args in the t_pipex struct
   Actions:
	1. Retrieves the command args in argv[1] to argv[n-1]. Use ft_split
	2. If any of the malloc fails, set cmd args as NULL and return
*/
void	init_cmd_args(t_pipex *pp, int argc, char *argv[])
{
	char	**cmd_arg;
	int		i;
	int		j;

	i = 2;
	j = 0;
	while (i < argc - 1)
	{
		cmd_arg = ft_split(argv[i], ' ');
		if (cmd_arg == NULL)
		{
			//probably needs a function here to clean up all the previous pp->cmd arg mallocs
			pp->cmd_args = NULL;
			return;
		}
		pp->cmd_args[j] = cmd_arg;
		i++;
		j++;
	}
}








int main(int argc, char *argv[], char *envp[])
{
    t_pipex *pp;
	char	**paths;
	int		i;
	int		j;
	char	*cmds;

    // char    *args[] = {"ls", NULL};
    // char    *envp[] = {NULL};

    // execve("/usr/bin/ls", args, envp);
    printf("No. of argc: %d\n", argc);
    pp = init_pipex(argc - 3);
	paths = get_paths(envp);

    printf("Argument count: %d\n", pp->cmd_num);
	i = 0;
	while (paths[i] != NULL)
	{
		printf("path: %s\n", paths[i]);
		i++;
	}

	// cmds = ft_split(argv[1], ' ')[0];
	// printf("Split commands. 0[%s]\n", cmds);
	// cmds = ft_pathjoin(paths[4], cmds);
	// printf("Try path.join: %s\n", cmds);
	// printf("File: %s, Execute access: %d\n", cmds, access(cmds, X_OK));

	j = 0;
	init_cmd_paths(pp, argc, argv, paths);
	init_cmd_args(pp, argc, argv);
	while (j < pp->cmd_num)
	{
		printf("Command path: %s\n", pp->cmd_paths[j]);
		printf("Command arg: 0[%s] 1[%s]\n", pp->cmd_args[j][0], pp->cmd_args[j][1]);
		j++;
	}

}
