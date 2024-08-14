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


/* Description: Closes the infile and outfile. Only closes if the fd >= 0.
   Function should only be used after file opening.
*/
void	close_files(t_pipex *pp)
{
    if (pp->fd_in >= 0)
		close(pp->fd_in);
	if (pp->fd_out >= 0)
		close(pp->fd_out);
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









