/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:57:57 by mintan            #+#    #+#             */
/*   Updated: 2024/08/06 20:39:37 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"

/* Description: Closes the infile and outfile. Only closes if the fd >= 0.
   Function should only be used after file opening.
*/
void	close_files(t_pipex *pp)
{
    if (pp->fd_in >= 0)
		close(pp->fd_in);
	if (pp->fd_out >= 0)
		close(pp->fd_out);
}

/* Description: Opens the infile and outfile and add them to the
   struct.
   Actions:
	- Opens the infile with O_RDONLY
	- Opens the outfile with O_CREATE, O_EXCL and O_WRONLY
*/
void	init_files(t_pipex *pp, char *infile, char *outfile)
{
	pp->fd_in = open(infile, O_RDONLY);
	pp->fd_out = open(outfile, O_CREAT | O_WRONLY);
	if (pp->fd_in == -1 || pp->fd_out == -1)
	{
		close_files(pp);
		//probably need some clean up function to handle all the things in side pp before exiting
		exit(EXIT_FAILURE);
	}
}











// int main(int argc, char *argv[], char *envp[])
// {
//     t_pipex *pp;
// 	char	**paths;
// 	int		i;
// 	char	*cmds;

//     // char    *args[] = {"ls", NULL};
//     // char    *envp[] = {NULL};

//     // execve("/usr/bin/ls", args, envp);
//     printf("No. of args: %d\n", argc);
//     pp = init_pipex(argc);
// 	paths = get_paths(envp);

//     printf("Argument count: %d\n", pp->cmd_num);
// 	i = 0;
// 	while (paths[i] != NULL)
// 	{
// 		printf("path: %s\n", paths[i]);
// 		i++;
// 	}

// 	cmds = ft_split(argv[1], ' ')[0];
// 	printf("Split commands. 0[%s]\n", cmds);
// 	cmds = ft_pathjoin(paths[4], cmds);
// 	printf("Try path.join: %s\n", cmds);
// 	printf("File: %s, Execute access: %d\n", cmds, access(cmds, X_OK));

// }
