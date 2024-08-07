/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:54:48 by mintan            #+#    #+#             */
/*   Updated: 2024/08/03 17:35:04 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* Description: xxxxxxx
*/

int main(void)
{
    int     access_res;
    char    file[] = "/usr/bin/ls";

    access_res = access(file, F_OK);
    printf("File: %s, File exists: %d\n", file, access_res);
    if (access_res < 0)
        perror("");
    access_res = access(file, R_OK);
    printf("File: %s, Read access: %d\n", file, access_res);
    if (access_res < 0)
        perror("");
    access_res = access(file, W_OK);
    printf("File: %s, Write access: %d\n", file, access_res);
    if (access_res < 0)
        perror("");
    access_res = access(file, X_OK);
    printf("File: %s, Execute access: %d\n", file, access_res);
    if (access_res < 0)
        perror("");
}
