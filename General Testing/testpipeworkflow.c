/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testpipeworkflow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 05:02:38 by mintan            #+#    #+#             */
/*   Updated: 2024/08/06 09:14:29 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Description: test using pipe, fork, dup and wait to simulate 2 commands

*/


#include "include/pipex.h"

int	main(void)
{
	int	fd[2];
	int	pid_1;
	int pid_2;
	int	pid_3;
	int	fd_infile;
	int	fd_outfile;

	fd_infile = open("newfile", O_RDONLY);
	fd_outfile = open("outfile", O_WRONLY);
	printf("fd_infile: %d | fd_outfile: %d\n", fd_infile, fd_outfile);
	if (pipe(fd) == -1)
	{
		perror("");
		return (1);
	}

	pid_1 = fork();
	if (pid_1 < 0)
	{
		perror("");
		return (2);
	}

	if (pid_1 == 0)
	{
		//child process 1. Execute first command
		//execve does takes over the process and does not return anything
		//dup2 to duplicate write into the pipe from standard output
		printf("In child process 1\n");
		dup2(fd[1], STDOUT_FILENO);
		dup2(fd_infile, STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);

		char	*args[] = {"grep", "msg", NULL};
		char	*envp[] = {NULL};
		execve("/usr/bin/grep", args, envp);
	}

	waitpid(pid_1, NULL, 0);

	pid_2 = fork();
	if (pid_2 < 0)
	{
		perror("");
		return (3);
	}


	if (pid_2 == 0)
	{
		//child process 2. Execute second command
		dup2(fd[0], STDIN_FILENO);
		dup2(fd_outfile, STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);

		printf("In child process 2\n");

		char	*args[] = {"wc", "-l", NULL};
		char	*envp[] = {NULL};
		execve("/usr/bin/wc", args, envp);
	}

	close(fd[0]);
	close(fd[1]);


	waitpid(pid_2, NULL, 0);



	return (0);


}
