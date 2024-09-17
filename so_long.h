/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:08:05 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/16 20:43:41 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <stdio.h>
#include <stdlib.h>
#include "./mlx_linux/mlx.h"
#include "./libft/libft.h"
#include "./get_next_line/get_next_line.h"
#include <fcntl.h>
//imgs
#define WALL_IMG "./imgs/wall.xpm"
#define FLOOR_IMG "./imgs/floor.xpm"
#define BACK_IMG "./imgs/back_floor.xpm"
#define FRONT_IMG "./imgs/front_floor.xpm"
#define LEFT_IMG "./imgs/left_floor.xpm"
#define RIGHT_IMG "./imgs/right_floor.xpm"
#define COLLECTIBLE_IMG "./imgs/collectible.xpm"
#define EXIT_IMG "./imgs/exit.xpm"
#define ENTRANCE_IMG "./imgs/entrance.xpm"
//keys
#define RIGHT_ARROW 65363
#define LEFT_ARROW 65361
#define UP_ARROW 65362
#define DOWN_ARROW 65364
#define ESC 65307
#define W_KEY 119
#define D_KEY 100
#define A_KEY 97
#define S_KEY 115

typedef struct s_img
{
	void	*img_ptr;
	int		width;
	int		height;
}	t_img;


typedef struct s_data
{
	void	*mlx;
	void	*win;
	char	**map;
	int		map_width;
	int		map_height;
	int		x_player;
	int		y_player;
	int		collectibles;
	int		collected;
	t_img	img_front;
	t_img	img_right;
	t_img	img_left;
	t_img	img_back;
	t_img	img_exit;
	t_img	img_entrence;
	t_img	img_collectible;
	t_img	img_wall;
	t_img	img_floor;
	int		moves;
	int		exit_x;
	int		exit_y;
}	t_data;

typedef struct s_elements
{
	int colectibles;
	int exit;
}	t_elements;


#define IMG_SIZE 32

#endif