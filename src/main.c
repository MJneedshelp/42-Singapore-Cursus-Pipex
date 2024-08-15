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
*/

t_pipex *init_pipex(int cmd_num)
{
    t_pipex *pp;

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

char    **get_paths(char *envp[])
{
    char    *path;
    char    **paths;

    path = NULL;
    while(*envp)
    {
        if (ft_strncmp(*envp, "PATH=", 5) == 0)
            path = ft_substr(*envp, 5, ft_strlen(*envp));
        envp++;
    }
    if (path == NULL)
        return (NULL);
    paths = ft_split(path, ':');
	free(path);
    return (paths);
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
	t_pipex *pp;
	char	**paths;

	if (strncmp(argv[1], "here_doc", 9) == 0 && ft_strlen(argv[1]) == 8)
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
	paths = get_paths(envp);
	if (paths == NULL)
		free_pipex_empty(pp);
	init_cmd_paths(pp, argc, argv, paths);
	init_cmd_args(pp, argc, argv);
	exe_cmd(pp);
	free_ft_split(paths);
	close_files(pp);
	free_pipex(pp);
}


//here_doc logic
//use gnl to read and write into a temp file
//use the temp file as the infile for init file
//gotta unlink the file at the end

