/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mintan <mintan@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 17:23:17 by mintan            #+#    #+#             */
/*   Updated: 2024/06/29 12:27:08 by mintan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* get_next_line functions */
char	*get_next_line(int fd);
void	freemem(char **rem, char *buff);
char	*remcheck(char **rem, int npos);
int		findn(char *str);

/* Utility functions */
size_t	gnl_strlen(const char *str);
void	*gnl_memmove(void *dest, const void *src, size_t n);
char	*gnl_substr(char const *s, unsigned int start, size_t len);
char	*gnl_strjoin(char **s1, char *s2);
char	*gnl_strdup(char **s);

#endif
