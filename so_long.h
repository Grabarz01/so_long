/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:08:05 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/17 15:01:55 by fgrabows         ###   ########.fr       */
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
#define IMG_SIZE 32
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
//structures
typedef struct s_img
{
	void	*img_ptr;
	int		width;
	int		height;
}		t_img;

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
}		t_data;

typedef struct s_elements
{
	int colectibles;
	int exit;
}		t_elements;
//functions
void	ft_move_down(t_data *data);
void	ft_move_up(t_data *data);
void	ft_move_left(t_data *data);
void	ft_move_right(t_data *data);
int		ft_change_pos(int keycode, t_data *data);
void	ft_error_message(char *str, int num);
void	ft_error_manager(int x);
void	ft_print_moves(int moves);
void	ft_free_split(char **args);
void	ft_free_imgs(t_data *data);
void	ft_free_everything(t_data *data);
void	ft_element_access(char **map_copy, int x, int y, t_elements *access);
void	ft_walls(t_data *data);
int		ft_count_elements(char element, t_data *data);
void	ft_elements(char **map, t_data *data, int n, int m);
void	ft_get_size(int fd, t_data *data);
int		ft_check_next_object(int x, int y, t_data *data);
void	ft_win(int x, int y, t_data *data);
void	ft_collection(t_data *data);
int		ft_close(t_data *data);
void	ft_hooks(t_data *data);
void	ft_set_ptrs(t_data *data);
void	ft_starting_point(int x, int y, t_data *data);
void	ft_exit_point (int x, int y, t_data *data);
char	**ft_map_copy(t_data *data);
void	ft_set_map(int fd, t_data *data);
void	ft_check_line(char *buff, t_data *data);
void	ft_allocate_map_memory(t_data *data);
void	ft_put_img(int x, int y, t_data *data);
void	ft_render_map(t_data *data);
void	ft_init_imgs(char *path, t_data *data, t_img *img);
void	ft_all_init(t_data *data);
void	ft_check_map(int fd, t_data *data);
void	ft_input_checker(int argc, char **argv);
void	ft_map_checker(char *map, t_data *data);

#endif