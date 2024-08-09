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


/* Main logic


    1. create pipe
    2. fork to get a child process
        a. in parent process, close the write end of the pipe. Leave the read end of the pipe open to receive information from child process
        b. in child process, close the read  end of the pipe. Leave the write end of the pipe open to pass back the output of execve back to parent process
    3. execute the shell command in the child process using execve. Execve takes over the process
    4.
    5. Parent waitpid(). Waits for child process, which is executing the execve, to end.




    probably have a function that is executed in the child process that runs execve
        takes in a command, the inputs
    all the execve should be run in child processes


    Main logic
    1. validate inputs
        a. check number of argc, argv[]
        b. check input file exists
            - XXXXXXX need to know the behaviour if the input file does not exist
        c. check output file exist
            - if it does exist -> check writable
                - check if error handling needs to be done here or if execve already handles this portion by default
            - if it does not exist -> create

    2. pipe():
        a. for n commands, create (n - 1) pipes
        b. malloc an array (n -1) of arrays {{0, 1}, {0, 1}, {0, 1}, {0, 1}} to store the all the child process PIDs.

    3. fork():
        a. for n commands, create n child processes. Child processes should only be created from the parent process
        b. each child process should have access to all the pipes created previously

    4. close

    validate number of argc, argv[]
        a. argc must be equal to 5






*/

/* Description: XXXXX

*/

int main(int argc, char *argv[], char *envp[])
{

    t_pipex	*pp;

	// Check if there are at least 4 arguments
	if (argc < 5)
		return (1);
	pp = init_pipex(argc - 3);
	if (pp == NULL)
		return (2);



	//might want to combine all the init stuff together in 1 function
    //1. Init pipex structure

    //2. Check if there are at least 4 arguments -> done

    //3. get cmds from the argv[]

    //4. get cmd arguments from argv[]

}


int	main(int argc, char *argv[], char *envp[])
{
    t_pipex *pp;
	int		i;
	int		j;
	char	*cmds;

	j = 0;
    printf("Inside the main to test init\n");
	printf("No. of argc: %d\n", argc);
    pp = init_main(argc, argv, envp);
	//check all the shit inside the structure
    printf("No. of commands: %d\n", pp->cmd_num);

	while (j < pp->cmd_num)
	{
		printf("Command path: %s\n", pp->cmd_paths[j]);
		printf("Command arg: 0[%s] 1[%s]\n", pp->cmd_args[j][0], pp->cmd_args[j][1]);
		j++;
	}
	printf("Infile fd: %d | Outfile fd: %d\n", pp->fd_in, pp->fd_out);
	exe_cmd(pp);



}
