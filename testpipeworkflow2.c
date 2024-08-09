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

#include "include/pipex.h"

int	main(void)
{
	int	fd[2];
	int	pid_1;
	int pid_2;
	int	pid_3;
	int	fd_infile;
	int	fd_outfile;
	int	cmd_counter;
	int	fd_input;
	int	fd_output;
	int	pid_child;
	char	*envp[] = {NULL};
	char	*cmd = "test";
	char	*args[] = {NULL};

	cmd_counter = 0;
	fd_infile = open("newfile", O_RDONLY);
	fd_outfile = open("outfile", O_WRONLY);
	printf("fd_infile: %d | fd_outfile: %d\n", fd_infile, fd_outfile);

	while (cmd_counter < 4)		//this whole thing can be put in a function
	{
		if (pipe(fd) == -1)
		{
			perror("Piping failed\n");
			return (1);
		}
		pid_child = fork();
		if (pid_child < 0)
		{
			perror("forking failed\n");
			return (2);
		}
		if (pid_child == 0)
		{
			//inside child process now where the command is to be executed
			//Adjust the input source in the child process
				//If this is the first child, read from INFILE
				//else, read fd[0] of the previous [pipe]
			if (cmd_counter == 0)	//  probably can use the cmd_count in the structure
			{
				//first cmd -> clone old FD (infile) into new FD (STDIN_FILENO)
				//read from infile instead of STDIN
				dup2(fd_infile, STDIN_FILENO);
			}
			else
			{
				//second command onwards, read from the read end of the previous pipe. This FD was assigned in the previous iteration
				dup2(fd_input, STDIN_FILENO);
			}
			//Adjust the output of the child process
				//If this is the final child, write to the outfile
				//else write to the write end of the pipe
			if(cmd_counter == 4 - 1)
			{
				//final command -> clone old FD (outfile) into the new FD (STDOUT_FILENO)
				//write into outfile instead of STDIN
				dup2(fd_outfile, STDOUT_FILENO);
			}
			else
			{
				//write into the write end of the pipe
				dup2(fd[1], STDOUT_FILENO);
			}

			close(fd[0]);
			close(fd[1]);

			//execute commands
			if (cmd_counter == 0)
			{
				char	*args1[] = {"cat", NULL};
				execve("/usr/bin/cat", args1, NULL);
			}
			else if (cmd_counter == 1)
			{
				char	*args2[] = {"grep", "Symbol", NULL};
				execve("/usr/bin/grep", args2, NULL);
			}
			else if (cmd_counter == 2)
			{
				char	*args2[] = {"grep", "1", NULL};
				execve("/usr/bin/grep", args2, NULL);
			}
			else
			{
				char	*args3[] = {"wc", "-l", NULL};
				execve("/usr/bin/wc", args3, NULL);
			}
		}

		//set in parent process
		//set the fd_input for the next iteration as the read end of the pipe
		fd_input = fd[0];
		close(fd[1]);
		cmd_counter++;
		waitpid(pid_child, NULL, 0);
	}
	return(0);
}
