/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:57:29 by mintan            #+#    #+#             */
/*   Updated: 2024/08/17 19:06:58 by mintan           ###   ########.fr       */
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
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
		// dup2(fd_in, STDIN_FILENO);
	if (ctr == pp->cmd_num - 1)
		dup2(pp->fd_out, STDOUT_FILENO);
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
}

/* Description: creates a pipe if it is not the final command
*/

int	*create_pipe(t_pipex *pp, int ctr, int *fd, char **paths)
{
	if (ctr < pp->cmd_num - 1)
	{
		if (pipe(fd) == -1)
			pipex_cleanup(pp, paths, EXIT_FAILURE);
	}
	return (fd);
}

/* Description: Closes all unused file descriptors in the parent process.
   Reassigns the read end of the pipe for the next command. Only executes
   this before the final command; no pipe is created for the final command.
*/

int	close_pipe_fd(t_pipex *pp, int ctr, int *fd)
{
	if (ctr < pp->cmd_num)
	{
		close(fd[1]);
		return (fd[0]);
	}
	return (STDIN_FILENO);
}

/* Description: waits for all the child processes to end in the parent process.
   Waits for 1 less child process if the infile is /dev/random or /dev/urandom
*/

void	wait_children(t_pipex *pp)
{
	int	ctr;

	// if (pp->infile_random == 1)
	// 	ctr = 1;
	// else
	// 	ctr = 0;
	ctr = 0;
	while (ctr < pp->cmd_num)
	{
		wait(NULL);
		ctr++;
	}
}

/* Description: Executes all the commands given
   Actions: perform the following in a loop until all commands are executed
	1. Create a pipe if it is not the final command
	2. Create a child process to execute the command
	3. Within the child process:
	   - Redirect the inputs and outputs of the process
	   - Execute the command using execve. Execve takes over the child process
	     if it does not fail
	   - Exit the child process if the execve encounters and error and fails
	4. In the parent process:
	   - Wait for the child process to end after all the pipes and child
	     processes are created
	   - Close all unused fds on the pipe
*/

void	exe_cmd(t_pipex *pp, char **paths)
{
	int	fd[2];
	int	ctr;
	int	pid_chd;
	int	fd_in;

	ctr = 0;
	while (ctr < pp->cmd_num)
	{
		create_pipe(pp, ctr, fd, paths);
		pid_chd = fork();
		if (pid_chd < 0)
			pipex_cleanup(pp, paths, EXIT_FAILURE);
		if (pid_chd == 0)
		{
			redirection(fd, ctr, pp, fd_in);
			execve(pp->cmd_paths[ctr], pp->cmd_args[ctr], NULL);
			pipex_cleanup(pp, paths, EXIT_FAILURE);
		}
		// if (pp->infile_random == 1 && ctr == 0)
		// 	waitpid(pid_chd, NULL, WNOHANG);
		fd_in = close_pipe_fd(pp, ctr, fd);
		ctr++;
	}
	wait_children(pp);
}
