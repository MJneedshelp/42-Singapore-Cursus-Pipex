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
	char	**cmd_paths;
	char	***cmd_args;
	int		cmd_num;
	int		fd_in;
	int		fd_out;
	char	*here_doc_path;
	int		infile_random;
}	t_pipex;

/* Initialisation functions */
t_pipex	*init_pipex(int cmd_num);
char	**get_paths(char *envp[], t_pipex *pp);
void	init_files(t_pipex *pp, char *infile, char *outfile);
void	check_infile_random(t_pipex *pp, char *infile);
void	init_cmd_paths(t_pipex *pp, int argc, char *argv[], char **paths);
void	init_cmd_args(t_pipex *pp, int argc, char *argv[]);
char	*get_cmd(char *full_cmd);
char	*get_cmd_path(char *full_cmd, char **paths);
void	redirection(int *fd, int ctr, t_pipex *pp, int fd_in);
int		*create_pipe(t_pipex *pp, int ctr, int *fd, char **paths);
int		close_pipe_fd(t_pipex *pp, int ctr, int *fd);
void	exe_cmd(t_pipex *pp, char **paths);

/* Bonus functions*/
void	init_files_here_doc(t_pipex *pp, char *limit, char *outfile);
void	init_here_doc_temp(t_pipex *pp);
void	populate_here_doc(t_pipex *pp, char *limit);

/* Clean up functions */
void	free_pipex_empty(t_pipex *pp);
void	pipex_cleanup(t_pipex *pp, char **paths, int exit_code);
void	free_stray(char **arr, int n);
void	free_astray(char ***arr, int n);
void	free_ft_split(char **arr);
void	close_files(t_pipex *pp);

#endif
