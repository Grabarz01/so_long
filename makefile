# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/03 19:06:41 by fgrabows          #+#    #+#              #
#    Updated: 2024/09/17 13:51:30 by fgrabows         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = gcc
FLAGS = -Wall -Wextra -Werror
GNL_PATH = ./get_next_line/
LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)libft.a
C_FILES = main.c $(GNL_PATH)get_next_line.c $(GNL_PATH)get_next_line_utils.c $(GNL_PATH)get_next_line.h
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

fclean:
	make -C $(LIBFT_PATH) fclean
	rm -rf $(NAME) 

re: fclean all
	
PHONY: all re clean fclean