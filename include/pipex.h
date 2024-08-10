/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:55:37 by mintan            #+#    #+#             */
/*   Updated: 2024/08/06 20:34:53 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H


# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "libft.h"

typedef struct s_pipex
{
    char	**cmd_paths;        //array of strings.
    char	***cmd_args;        //arrary of array of strings. Should be NULL terminated for both levels of arrays
    int		cmd_num;            //number of commands
    int		fd_in;            //infile from main(argv) -> check if you need this in the struct
    int		fd_out;           //outfile from main(argv) -> check if you need this in the struct
}   t_pipex;





/* Initialisation functions */
t_pipex	*init_pipex(int cmd_num);
char	**get_paths(char *envp[]);
void	close_files(t_pipex *pp);
t_pipex	*init_main(int argc, char *argv[], char *envp[]);
void	init_files(t_pipex *pp, char *infile, char *outfile);
void	init_cmd_paths(t_pipex *pp, int argc, char *argv[], char **paths);
void	init_cmd_args(t_pipex *pp, int argc, char *argv[]);
int		exe_cmd(t_pipex *pp);
void	redirection(int *fd, int ctr, t_pipex *pp, int fd_in);




#endif
