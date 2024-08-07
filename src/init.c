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

/* Description: Initialises the t_pipex structure by allocating memory with
   malloc for the following members:
   - cmd_num: number of commands passed in from argv[]
   - cmd_paths: an array of strings containing the full file path of each of the
     binaries
   - cmd_arg: an array of array of strings containg the arguments to be used
   for each command
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










// int main(int argc, char *argv[], char *envp[])
// {
//     t_pipex *pp;
// 	char	**paths;
// 	int		i;
// 	char	*cmds;

//     // char    *args[] = {"ls", NULL};
//     // char    *envp[] = {NULL};

//     // execve("/usr/bin/ls", args, envp);
//     printf("No. of args: %d\n", argc);
//     pp = init_pipex(argc);
// 	paths = get_paths(envp);

//     printf("Argument count: %d\n", pp->cmd_num);
// 	i = 0;
// 	while (paths[i] != NULL)
// 	{
// 		printf("path: %s\n", paths[i]);
// 		i++;
// 	}

// 	cmds = ft_split(argv[1], ' ')[0];
// 	printf("Split commands. 0[%s]\n", cmds);
// 	cmds = ft_pathjoin(paths[4], cmds);
// 	printf("Try path.join: %s\n", cmds);
// 	printf("File: %s, Execute access: %d\n", cmds, access(cmds, X_OK));

// }
