# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mintan <mintan@student.42singapore.sg      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 22:10:59 by mintan            #+#    #+#              #
#    Updated: 2024/06/05 21:42:44 by mintan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler + compile flags
CC = cc
CFLAGS = -Wall -Werror -Wextra -c

# Definitions
NAME = libft.a
SOURCES = ft_atoi.c ft_atol.c ft_lstiter.c ft_puthexa.c ft_strlcpy.c ft_bzero.c ft_lstlast.c ft_putnbr.c ft_strlen.c ft_calloc.c ft_lstmap.c ft_putnbr_fd.c ft_strmapi.c ft_isalnum.c ft_lstnew.c ft_putptr.c ft_strncmp.c ft_isalpha.c ft_lstsize.c ft_putstr.c ft_strnstr.c ft_isascii.c ft_memchr.c ft_putstr_fd.c ft_strrchr.c ft_isdigit.c ft_memcmp.c ft_putunsignednbr.c ft_strtrim.c ft_isprint.c ft_memcpy.c ft_split.c ft_substr.c ft_itoa.c ft_memmove.c ft_strchr.c ft_tolower.c ft_lstadd_back.c ft_memset.c ft_strdup.c ft_toupper.c ft_lstadd_front.c ft_printf.c ft_striteri.c ft_lstclear.c ft_putchar_fd.c ft_strjoin.c ft_pathjoin.c ft_lstdelone.c ft_putendl_fd.c ft_strlcat.c ft_least.c
OBJECTS = $(SOURCES:.c=.o)

# Target to make using Make all
all: $(NAME)

# Rule to create the LIBRARY
# r > add specified files into ar | c > create archive| s > write index to ar
# "@" > Target | "^" > Prerequisites
$(NAME): $(OBJECTS)
	ar rcs $@ $^

# Rule to create the OBJECTS
# "<" > Prerequisites

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

# Clear the build files
clean:
	rm -f $(OBJECTS) $(BONUSOBJS)

fclean: clean
	rm -f $(NAME)

# Rule to rebuild the target
re:	fclean all

# Phony targets
.PHONY: all clean re fclean
