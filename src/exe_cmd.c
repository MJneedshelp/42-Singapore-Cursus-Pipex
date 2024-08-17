/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:57:29 by mintan            #+#    #+#             */
/*   Updated: 2024/08/16 17:50:40 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include "../include/ft_printf.h"


/* Description: uses dup2 to redirect the inputs for each command. Commands
   always read from stdin and outputs to stdout
   Actions:
	1. When executing the first command, clone the infile_fd to stdin
	2. When executing subsequent commands, clone the read end of the pipe to
	   stdin. Clone the write end of the pipe to stdout
	3. When executing the final command, clone the outfile_fd to stdout
	4. Close all the unused fds on the pipe
*/

void	redirection(int *fd, int ctr, t_pipex *pp, int fd_in)
{
	if (ctr == 0)
	{
		dup2(pp->fd_in, STDIN_FILENO);
	}
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

int	exe_cmd(t_pipex *pp)
{
	int	fd[2];
	int	ctr;
	int	pid_chd;
	int	fd_in;

	ctr = 0;
	while (ctr < pp->cmd_num)
	{
		if (ctr < pp->cmd_num - 1)
		{
			if (pipe(fd) == -1)
				return (perror(""), 1);
		}
		pid_chd = fork();
		if (pid_chd < 0)
			return (perror(""), 2);
		if (pid_chd == 0)
		{
			redirection(fd, ctr, pp, fd_in);
			execve(pp->cmd_paths[ctr], pp->cmd_args[ctr], NULL);
			exit(EXIT_FAILURE);
		}
		waitpid(pid_chd, NULL, 0);
		if (ctr < pp->cmd_num)
		{
			fd_in = fd[0];
			close(fd[1]);
		}
		ctr++;
	}
	return (0);
}
