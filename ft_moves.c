/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_moves.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:06:10 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/17 14:08:12 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_move_down(t_data *data)
{
	int access;

	access = ft_check_next_object(data->x_player, data->y_player + 1, data);
	if (access == 0)
		mlx_put_image_to_window(data->mlx, data->win, data->img_front.img_ptr,
		 data->x_player * IMG_SIZE , data->y_player * IMG_SIZE);
	else
	{
		if(data->map[++data->y_player][data->x_player] == 'C')
			ft_collection(data);
		if(data->map[data->y_player][data->x_player] == 'E')
			ft_win(data->x_player, data->y_player - 1, data);
		data->map[data->y_player - 1][data->x_player] = '0';
		mlx_put_image_to_window(data->mlx, data->win, data->img_front.img_ptr,
			data->x_player * IMG_SIZE , data->y_player * IMG_SIZE);
		mlx_put_image_to_window(data->mlx, data->win, data->img_floor.img_ptr,
			data->x_player * IMG_SIZE , (data->y_player - 1) * IMG_SIZE);
		ft_print_moves(++data->moves);
	}
}
void ft_move_up(t_data *data)
{
	int access;

	access = ft_check_next_object(data->x_player, data->y_player - 1, data);
	if (access == 0)
		mlx_put_image_to_window(data->mlx, data->win, data->img_back.img_ptr,
		 data->x_player * IMG_SIZE , data->y_player * IMG_SIZE);
	else
	{
		if(data->map[--data->y_player][data->x_player] == 'C')//2
			ft_collection(data);
		if(data->map[data->y_player][data->x_player] == 'E')
		{//3
			ft_win(data->x_player, data->y_player + 1, data);//3
		}
		data->map[data->y_player + 1][data->x_player] = '0';//1
		mlx_put_image_to_window(data->mlx, data->win, data->img_back.img_ptr,
			data->x_player * IMG_SIZE , data->y_player * IMG_SIZE);
		mlx_put_image_to_window(data->mlx, data->win, data->img_floor.img_ptr,
			data->x_player * IMG_SIZE , (data->y_player + 1) * IMG_SIZE);
		ft_print_moves(++data->moves);
	}
}
void ft_move_left(t_data *data)
{
	int access;

	access = ft_check_next_object(data->x_player - 1, data->y_player, data);
	if (access == 0)
		mlx_put_image_to_window(data->mlx, data->win, data->img_left.img_ptr,
		 data->x_player * IMG_SIZE , data->y_player * IMG_SIZE);
	else
	{
		if(data->map[data->y_player][--data->x_player] == 'C')
			ft_collection(data);
		if(data->map[data->y_player][data->x_player] == 'E')
		{
			ft_win(data->x_player + 1, data->y_player, data);
		}
		data->map[data->y_player][data->x_player + 1] = '0';
		mlx_put_image_to_window(data->mlx, data->win, data->img_left.img_ptr,
			data->x_player * IMG_SIZE , data->y_player * IMG_SIZE);
		mlx_put_image_to_window(data->mlx, data->win, data->img_floor.img_ptr,
			(data->x_player + 1) * IMG_SIZE , data->y_player * IMG_SIZE);
		ft_print_moves(++data->moves);
	}
}
void ft_move_right(t_data *data)
{
	int access;
	
	access = ft_check_next_object(data->x_player + 1, data->y_player, data);
	if (access == 0)
		mlx_put_image_to_window(data->mlx, data->win, data->img_right.img_ptr,
		 data->x_player * IMG_SIZE , data->y_player * IMG_SIZE);
	else
	{
		if(data->map[data->y_player][++data->x_player] == 'C')
			ft_collection(data);
		if(data->map[data->y_player][data->x_player]== 'E')
		{
			ft_win(data->x_player - 1, data->y_player, data);
		}
		data->map[data->y_player][data->x_player - 1] = '0';
		mlx_put_image_to_window(data->mlx, data->win, data->img_right.img_ptr,
			data->x_player * IMG_SIZE , data->y_player * IMG_SIZE);
		mlx_put_image_to_window(data->mlx, data->win, data->img_floor.img_ptr,
			(data->x_player - 1) * IMG_SIZE , data->y_player * IMG_SIZE);
		ft_print_moves(++data->moves);
	}
}

int ft_change_pos(int keycode, t_data *data)
{
	if(keycode == W_KEY || keycode == UP_ARROW)
		ft_move_up(data);
	if(keycode == S_KEY || keycode == DOWN_ARROW )
		ft_move_down(data);
	if(keycode == A_KEY || keycode == LEFT_ARROW )
		ft_move_left(data);
	if(keycode == D_KEY || keycode == RIGHT_ARROW)
		ft_move_right(data);
	if (keycode == ESC)
	{
		ft_putstr_fd("Leaving the program...\n", 1);
		ft_free_everything(data);
		exit(0);
	}
	return(0);
}