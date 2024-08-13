# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mintan <mintan@student.42singapore.sg      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/15 22:10:59 by mintan            #+#    #+#              #
#    Updated: 2024/07/07 20:03:21 by mintan           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler + compile flags
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Definitions
NAME = pipex
SRCDIR = src
LIBDIR = $(SRCDIR)/libft
LIBFT_LIB = $(LIBDIR)/libft.a
# Double check sources again
PIPEX_SRCS = $(SRCDIR)/main.c $(SRCDIR)/init.c $(SRCDIR)/init_files.c \
			$(SRCDIR)/init_cmds.c $(SRCDIR)/exe_cmd.c $(SRCDIR)/cleanup.c
PIPEX_OBJ = $(PUSHSWAP_SRCS:.c=.o)

# Target to make using Make all
all: $(NAME) print_art

# Generate the programme by compiling the objects with libft.a
$(NAME): $(LIBFT_LIB) $(PIPEX_OBJ)
	$(CC) $(CFLAGS) $(PIPEX_OBJ) $(LIBFT_LIB) -o $@

# Build the libft.a library
$(LIBFT_LIB):
	cd $(LIBDIR) && make all

# Generate all the .o files from the .c files for pipex
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Clear the build files
clean:
	rm -f $(PIPEX_OBJ)
	cd $(LIBDIR) && make clean

fclean: clean
	rm -f $(NAME)
	cd $(LIBDIR) && make fclean

# Rule to rebuild the target
re:	fclean all

# Phony targets
.PHONY: all clean re fclean

print_art:
	@echo"████████████████████████"
	@echo"██▒▒▒▒░░░░░░░░░░░░    ██"
	@echo"██▒▒▒▒░░░░░░░░░░░░    ██"
	@echo"████████████████████████"
	@echo"  ██▒▒▒▒░░░░░░░░░░░░██  "
	@echo"  ██▒▒▒▒░░░░░░░░░░░░██  "
	@echo"  ██▒▒▒▒░░░░░░░░░░░░██  "
	@echo"  ██▒▒▒▒░░░░░░░░░░░░██  "
	@echo"  ██▒▒▒▒░░░░░░░░░░░░██  "
	@echo"  ██▒▒▒▒░░░░░░░░░░░░██  "
	@echo"  ██▒▒▒▒░░░░░░░░░░░░██  "
	@echo"  ██▒▒▒▒░░░░░░░░░░░░██  "
	@echo"  ██▒▒▒▒░░░░░░░░░░░░██  "
	@echo"  ██▒▒▒▒░░░░░░░░░░░░██  "
