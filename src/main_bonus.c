/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:44:26 by mintan            #+#    #+#             */
/*   Updated: 2024/08/22 09:30:08 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include "../include/ft_printf.h"
#include "../include/get_next_line.h"

/* Description: Initialises the t_pipex structure by allocating memory with
   malloc for the following members:
   - cmd_num: number of commands passed in from argv[]
   - cmd_paths: an array of strings containing the full file path of each of the
     binaries. To be used as the first argument for execve()
   - cmd_arg: an array of array of strings containing the arguments to be used
   	 for each command. To be used as the second argument for execve()
   - here_doc_path: path used to store a temporary file to hold all the text
     in the here_doc. This value is only populated if a here_doc is used
*/

t_pipex	*init_pipex(int cmd_num)
{
	t_pipex	*pp;

	pp = (t_pipex *)malloc(sizeof(t_pipex));
	if (pp == NULL)
		exit (EXIT_FAILURE);
	pp->cmd_num = cmd_num;
	pp->cmd_paths = (char **)malloc(cmd_num * sizeof(char *));
	if (pp->cmd_paths == NULL)
	{
		free (pp);
		exit (EXIT_FAILURE);
	}
	pp->cmd_args = (char ***)malloc(cmd_num * sizeof(char **));
	if (pp->cmd_paths == NULL)
	{
		free (pp->cmd_paths);
		free (pp);
		exit (EXIT_FAILURE);
	}
	pp->here_doc_path = NULL;
	return (pp);
}

/* Description: Retrieves the PATH variable from the envp[]. envp[] is taken in
   from main. Returns a array of strings: char **paths.
*/

char	**get_paths(char *envp[], t_pipex *pp)
{
	char	*path;
	char	**paths;
	int		got_paths;

	path = NULL;
	while (*envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
		{
			path = ft_substr(*envp, 5, ft_strlen(*envp));
			got_paths = 1;
		}
		envp++;
	}
	if (path == NULL && got_paths == 1)
	{
		free_pipex_empty(pp);
		exit (EXIT_FAILURE);
	}
	if (path == NULL)
		return (NULL);
	paths = ft_split(path, ':');
	free(path);
	return (paths);
}

/* Description: prints out an error message to remind users to use the correct
   number of commands when running the pipex programme.
*/
void	print_arg_error_and_exit(void)
{
	ft_printf("Please run pipex in this fashion: \n");
	ft_printf("./pipex infile cmd1 cmd2 outfile OR\n");
	ft_printf("./pipex infile cmd1 cmd2 cmd3...cmdn outfile OR\n");
	ft_printf("./pipex here_doc LIMITER cmd1 cmd2 outfile\n");
	exit (EXIT_FAILURE);
}

/* Description: checks the number of arguments being passed into the pipex
   programme. Exits the programme if the minimum arguments are not provided.
   Also checks if the programme is running with here_doc.
   Return:
	- 0: not running with here_doc
	- 1: running with here_doc
*/
int	check_args(int argc, char *argv[])
{
	if (argc < 2)
		print_arg_error_and_exit();
	if (ft_strncmp(argv[1], "here_doc", 9) == 0 && ft_strlen(argv[1]) == 8)
	{
		if (argc < 6)
			print_arg_error_and_exit();
		return (1);
	}
	if (argc < 5)
		print_arg_error_and_exit();
	return (0);
}

/* Description: Main function of the programme. Simulates the pipe command.
   Actions:
	1. Checks if there are at least 5 argc (1 infile, 2 commands, 1 outfile)
	2. Initialise the pipex structure
	3. Initialise the infile and outfile
	4. Get environment paths: used to form the command paths
	5. Get the command paths for each command
	6. Get the command arguments for each command
	7. Execute the commands
	8. Close all open fds
	9. Free all allocated memory
*/

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pp;
	char	**paths;

	if (check_args(argc, argv) == 1)
	{
		if (argc < 6)
			return (1);
		pp = init_pipex(argc - 4);
		init_files_here_doc(pp, argv[2], argv[argc - 1]);
	}
	else
	{
		if (argc < 5)
			return (1);
		pp = init_pipex(argc - 3);
		init_files(pp, argv[1], argv[argc - 1]);
	}
	paths = get_paths(envp, pp);
	init_cmd_paths(pp, argc, argv, paths);
	init_cmd_args(pp, argc, argv);
	exe_cmd(pp, paths);
	pipex_cleanup(pp, paths, EXIT_SUCCESS);
}
