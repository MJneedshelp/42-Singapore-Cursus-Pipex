/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
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
#include "../include/get_next_line.h"


/* Description: Closes the infile and outfile. Only closes if the fd >= 0.
   Function should only be used after file opening.
*/
void	close_files(t_pipex *pp)
{
    if (pp->fd_in >= 0)
		close(pp->fd_in);
	if (pp->fd_out >= 0)
		close(pp->fd_out);
	if (pp->here_doc_path != NULL)
	unlink(pp->here_doc_path);
}

/* Description: Opens the infile and outfile and add them to the
   struct.
   Actions:
	- Checks access of infile with F_OK and R_OK
		- If access == -1, prints the error and open /dev/null as infile
		- If access == 0, opens the infile with O_RDONLY
	- Checks if outfile exists
		- If it does not exist, open and create the outfile and set its
		permissions
		- If it does exist,
			- No write permissions, clean up and exit
			- Has write permissions, open normally
*/
void	init_files(t_pipex *pp, char *infile, char *outfile)
{
	if (access(infile, F_OK | R_OK) < 0)
	{
		perror("");
		pp->fd_in = open("/dev/null", O_RDONLY);
	}
	else
		pp->fd_in = open(infile, O_RDONLY);
	if (access(outfile, F_OK) < 0)
		pp->fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
	{
		if (access(outfile, W_OK) < 0)
		{
			perror("");
			free_pipex_empty(pp);
			exit(EXIT_FAILURE);
		}
		else
			pp->fd_out = open(outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
	//might wanna check fd_in and fd_out for -1 and see how you wanna handle it here

}



void	populate_here_doc(t_pipex *pp, char *limit)
{
	char	*h_doc;

	while (1)
	{
		h_doc = get_next_line(0);
		write(pp->fd_in, h_doc, ft_strlen(h_doc));
		if ((ft_strncmp(h_doc, limit, ft_strlen(limit)) == 0) && \
		(ft_strlen(h_doc) == ft_strlen(limit) + 1))
		{
			free(h_doc);
			break;
		}
		free(h_doc);
	}


}


void	init_here_doc_temp(t_pipex *pp)
{
	pp->here_doc_path = ft_strdup("here_doc");
	if (pp->here_doc_path == NULL)
	{
		free(pp->here_doc_path);
		free_pipex_empty(pp);
		exit(EXIT_FAILURE);
	}
}



/* Description: Opens the infile and outfile and add them to the
   struct.
   Actions: XXXXX
	- Checks access of infile with F_OK and R_OK
		- If access == -1, prints the error and open /dev/null as infile
		- If access == 0, opens the infile with O_RDONLY
	- Checks if outfile exists
		- If it does not exist, open and create the outfile and set its
		permissions
		- If it does exist,
			- No write permissions, clean up and exit
			- Has write permissions, open normally
*/

void	init_files_here_doc(t_pipex *pp, char *limit, char *outfile)
{
	init_here_doc_temp(pp);
	pp->fd_in = open(pp->here_doc_path, O_CREAT | O_RDWR | O_APPEND);
	printf("here_doc fd: %d\n", pp->fd_in);
	populate_here_doc(pp, limit);
	if (access(outfile, F_OK) < 0)
		pp->fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
	{
		if (access(outfile, W_OK) < 0)
		{
			perror("");
			free_pipex_empty(pp);
			exit(EXIT_FAILURE);
		}
		else
			pp->fd_out = open(outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	}
	//might wanna check fd_in and fd_out for -1 and see how you wanna handle it here

}










