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
PIPEX_SRCS = $(SRCDIR)/main.c $(SRCDIR)/init_files.c \
			$(SRCDIR)/init_cmds.c $(SRCDIR)/exe_cmd.c $(SRCDIR)/cleanup.c \
			$(SRCDIR)/check_infile.c
PIPEX_OBJ = $(PIPEX_SRCS:.c=.o)

# Target to make using Make all
all: $(NAME) print_art
# all: $(NAME)

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
	@echo "                                                                                                         ''''''  "
	@echo "	SSSSSSSSSSSSSSS                                          kkkkkkkk             iiii                    '::::'    "
	@echo "	SS:::::::::::::::S                                         k::::::k            i::::i                   '::::'  "
	@echo "	S:::::SSSSSS::::::S                                         k::::::k             iiii                    ':::'' "
	@echo "	S:::::S     SSSSSSS                                         k::::::k                                    ':::'   "
	@echo "	S:::::S               mmmmmmm    mmmmmmm      ooooooooooo    k:::::k    kkkkkkkiiiiiiinnnn  nnnnnnnn    ''''    "
	@echo "	S:::::S             mm:::::::m  m:::::::mm  oo:::::::::::oo  k:::::k   k:::::k i:::::in:::nn::::::::nn          "
	@echo "	S::::SSSS         m::::::::::mm::::::::::mo:::::::::::::::o k:::::k  k:::::k   i::::in::::::::::::::nn          "
	@echo "	SS::::::SSSSS    m::::::::::::::::::::::mo:::::ooooo:::::o k:::::k k:::::k    i::::inn:::::::::::::::n          "
	@echo "		SSS::::::::SS  m:::::mmm::::::mmm:::::mo::::o     o::::o k::::::k:::::k     i::::i  n:::::nnnn:::::n        "
	@echo "		SSSSSS::::S m::::m   m::::m   m::::mo::::o     o::::o k:::::::::::k      i::::i  n::::n    n::::n           "
	@echo "				S:::::Sm::::m   m::::m   m::::mo::::o     o::::o k:::::::::::k      i::::i  n::::n    n::::n        "
	@echo "				S:::::Sm::::m   m::::m   m::::mo::::o     o::::o k::::::k:::::k     i::::i  n::::n    n::::n        "
	@echo "	SSSSSSS     S:::::Sm::::m   m::::m   m::::mo:::::ooooo:::::ok::::::k k:::::k   i::::::i n::::n    n::::n        "
	@echo "	S::::::SSSSSS:::::Sm::::m   m::::m   m::::mo:::::::::::::::ok::::::k  k:::::k  i::::::i n::::n    n::::n        "
	@echo "	S:::::::::::::::SS m::::m   m::::m   m::::m oo:::::::::::oo k::::::k   k:::::k i::::::i n::::n    n::::n        "
	@echo "	SSSSSSSSSSSSSSS   mmmmmm   mmmmmm   mmmmmm   ooooooooooo   kkkkkkkk    kkkkkkkiiiiiiii nnnnnn    nnnnnn         "
