/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testpipeworkflow.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 05:02:38 by mintan            #+#    #+#             */
/*   Updated: 2024/08/06 05:02:38 by mintan           ###   ########.fr       */
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
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/ls", {"ls", NULL}, {NULL});
	}

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
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/grep", {"grep", "test", NULL}, NULL);
	}

	close(fd[0]);
	close(fd[1]);

	waitpid(pid_1, NULL, 0);
	waitpid(pid_2, NULL, 0);



	return (0);


}
