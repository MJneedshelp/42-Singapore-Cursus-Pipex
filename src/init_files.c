/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 09:57:57 by mintan            #+#    #+#             */
/*   Updated: 2024/08/17 12:22:11 by mintan           ###   ########.fr       */
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

/* Description: Opens the infile and outfile and add them to the t_pipex
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
		perror(infile);
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
}

/* Description: uses get_next_line and reads from the standard input until
   the limiter is encountered. Stores all the read text without the limiter
   into a temporary file.
*/

void	populate_here_doc(t_pipex *pp, char *limit)
{
	char	*h_doc;

	while (1)
	{
		h_doc = get_next_line(0);
		if (h_doc == NULL)
		{
			free(h_doc);
			break ;
		}
		if ((ft_strncmp(h_doc, limit, ft_strlen(limit)) == 0) && \
		(ft_strlen(h_doc) == ft_strlen(limit) + 1))
		{
			free(h_doc);
			break ;
		}
		write(pp->fd_in, h_doc, ft_strlen(h_doc));
		free(h_doc);
	}
	close(pp->fd_in);
}

/* Description: activated only when there is a here_doc in the input.
   Initialises a path in which to create the temporary file to store
   the text for here_doc. Deletes the temporary file if it already exists.
*/

void	init_here_doc_temp(t_pipex *pp)
{
	pp->here_doc_path = ft_strdup("here_doc");
	if (pp->here_doc_path == NULL)
	{
		free(pp->here_doc_path);
		free_pipex_empty(pp);
		exit(EXIT_FAILURE);
	}
	if (access(pp->here_doc_path, F_OK) == 0)
		unlink(pp->here_doc_path);
}

/* Description: activated only when there is a here_doc in the input.
   Reads the input from the standard input and stores it in a temporary file.
   Stores the fds of the temporary file and the outfile in the in the t_pipex
   struct.
   Actions:
	1. Initialises the path to the temporary here_doc file
	2. Creates the temporary here_doc file and set its permissions
	3. Reads input from the standard input and closes the file. File must be
	   closed since the contents of the file has changed.
	4. Opens the temporary here_doc again
	5. Checks if outfile exists
		- If it does not exist, open and create the outfile and set its
		permissions
		- If it does exist,
			- No write permissions, clean up and exit
			- Has write permissions, open normally
*/

void	init_files_here_doc(t_pipex *pp, char *limit, char *outfile)
{
	init_here_doc_temp(pp);
	pp->fd_in = open(pp->here_doc_path, O_CREAT | O_RDWR | O_APPEND, 0644);
	populate_here_doc(pp, limit);
	pp->fd_in = open(pp->here_doc_path, O_RDONLY);
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
}
