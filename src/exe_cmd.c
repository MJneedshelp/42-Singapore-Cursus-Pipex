/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:57:29 by mintan            #+#    #+#             */
/*   Updated: 2024/08/13 10:28:04 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include "../include/ft_printf.h"




void	redirection(int *fd, int ctr, t_pipex *pp, int fd_in)
{
	if (ctr == 0)
		dup2(pp->fd_in, STDIN_FILENO);
	else
		dup2(fd_in, STDIN_FILENO);
	if (ctr == pp->cmd_num - 1)
		dup2(pp->fd_out, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}



/* Description: Executes all the commands given
   Actions: perform the following in a loop until all commands are executed
	1. Create a pipe
	2. Create a child process to execute the command


*/

void	exe_cmd(t_pipex *pp)
{
	int	fd[2];
	int	ctr;
	int	pid_chd;
	int	fd_in;

	ctr = 0;
	while (ctr < pp->cmd_num)
	{
		if (pipe(fd) == -1)
			// return (perror(""), 1);
			return;
		pid_chd = fork();
		if (pid_chd < 0)
			// return (perror(""), 2);
			return;
		if (pid_chd == 0)
		{
			redirection(fd, ctr, pp, fd_in);
			execve(pp->cmd_paths[ctr], pp->cmd_args[ctr], NULL);
		}
		fd_in = fd[0];
		close(fd[1]);
		waitpid(pid_chd, NULL, 0);
		ctr++;
	}
}
