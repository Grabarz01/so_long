/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:15:32 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/17 14:20:33 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_set_ptrs(t_data *data)
{
	data->mlx = NULL;
	data->win = NULL;
	data->img_back.img_ptr = NULL;
	data->img_front.img_ptr = NULL;
	data->img_left.img_ptr = NULL;
	data->img_right.img_ptr = NULL;
	data->img_wall.img_ptr = NULL;
	data->img_floor.img_ptr = NULL;
	data->img_exit.img_ptr = NULL;
	data->img_entrence.img_ptr = NULL;
	data->img_collectible.img_ptr = NULL;
	data->moves = 0;
	data->collected = 0;
}
void ft_starting_point(int x, int y, t_data *data)
{
	data->x_player = x;
	data->y_player = y;
}

void ft_exit_point (int x, int y, t_data *data)
{
	data->exit_x = x;
	data->exit_y = y;
}