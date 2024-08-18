/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testreadstdin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:02:40 by mintan            #+#    #+#             */
/*   Updated: 2024/08/15 16:23:12 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "include/libft.h"


int	main(int argc, char *argv[])
{
	char	*buff;

	printf("No of argc: %d\n", argc);
	printf("argv[0]: %s\n", argv[0]);
	printf("argv[1]: %s\n", argv[1]);

	buff = (char *)malloc(1024);

	if (ft_strncmp(argv[1], "here_doc", ft_strlen("here_doc")) == 0)
	{
		printf("first test works\n");
		read(STDIN_FILENO, buff, 1024);
		printf("Check buffer: %s\n", buff);
	}
	return (0);
}
