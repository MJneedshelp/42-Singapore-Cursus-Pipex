/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:57:57 by mintan            #+#    #+#             */
/*   Updated: 2024/08/06 20:39:37 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
#include "../include/libft.h"
#include "../include/ft_printf.h"

/* Description: Initialises the t_pipex structure by allocating memory with
   malloc for the following members:
   - cmd_num: number of commands passed in from argv[]
   - cmd_paths: an array of strings containing the full file path of each of the
     binaries. To be used as the first argument for execve()
   - cmd_arg: an array of array of strings containing the arguments to be used
   for each command. To be used as the second argument for execve()
   - TO ADD ON AS REQUIRED
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
    return (pp);
}






/* Description: Retrieves the PATH variable from the envp[]. envp[] is taken in
   from main. Returns a array of strings: char **paths.
*/

char    **get_paths(char *envp[])
{
    char    *path;
    char    **paths;
    int     i;

    i = 0;
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
    return (paths);
}



/* Description: main workflow for initialisation. Validates the incoming
   parameters and sets up the t_pipex structure.
   Actions:
    1. XXXXXXXXXX
*/
t_pipex	*init_main(int argc, char *argv[], char *envp[])
{
    t_pipex	*pp;
    char	**paths;


    if (argc < 5)
		exit(EXIT_FAILURE);
    pp = init_pipex(argc - 3);
    init_files(pp, argv[1], argv[argc - 1]);
    paths = get_paths(envp);
    if (paths == NULL)
	{
        //probably need a clean up function to settle the things inside the pp structure
	}
	init_cmd_paths(pp, argc, argv, paths);
	init_cmd_args(pp, argc, argv);
	return (pp);




    //probably need a clean up function to settle the things inside the pp structure

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



}
