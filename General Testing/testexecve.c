/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testexecve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:30:25 by mintan            #+#    #+#             */
/*   Updated: 2024/08/06 18:54:45 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char    *args[] = {"-l", NULL};
    char    *envp[] = {NULL};

    // execve("/usr/bin/ls", args, envp);
    execve("ls", args, envp);

	perror("");
	return (1);

}
