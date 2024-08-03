/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testexecve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 11:30:25 by mintan            #+#    #+#             */
/*   Updated: 2024/08/03 19:05:11 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int main(void)
{
    char    *args[] = {"ls", NULL};
    char    *envp[] = {NULL};

    execve("/usr/bin/ls", args, envp);

    printf("We are not going to see this\n");
    return (1);

}