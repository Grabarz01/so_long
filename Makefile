# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 19:06:41 by fgrabows          #+#    #+#              #
#    Updated: 2024/09/17 15:24:41 by fgrabows         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
FLAGS = -Wall -Wextra -Werror
GNL_PATH = ./get_next_line/
LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a
SO_LONG_FILES = errors_printables.c main.c ft_free.c ft_moves.c \
				map_validators.c move_validators.c my_mlx_hooks.c set_values.c \
				utils.c window_renders.c
C_FILES = $(SO_LONG_FILES) $(GNL_PATH)get_next_line.c $(GNL_PATH)get_next_line_utils.c
O_FILES = $(C_FILES:.c=.o)

all: $(NAME)

$(NAME): $(O_FILES) $(LIBFT)
	$(CC) $(O_FILES) $(FLAGS) $(LIBFT) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_PATH) all
	
%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(O_FILES)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -rf $(NAME) 

re: fclean all
	
.PHONY: all re clean fclean
