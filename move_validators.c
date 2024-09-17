/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_validators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:36:09 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/17 15:53:55 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_check_next_object(int x, int y, t_data *data)
{
	char	element;

	element = data->map[y][x]; 
	if (element == '1')
		return (0);
	if (element == 'E')
	{
		if (data->collected == data->collectibles)
			return (1);
		return (0);
	}
	return (1);
}
void	ft_win(int x, int y, t_data *data)
{
	ft_print_moves(++data->moves);
	mlx_put_image_to_window(data->mlx, data->win, data->img_floor.img_ptr,
		x * IMG_SIZE , y * IMG_SIZE);
	ft_putstr_fd("YOU ARE THE WINNER!!!\n", 1);
	ft_free_everything(data);
	exit(0);
}

void	ft_collection(t_data *data)
{
	data->collected++;
	if (data->collected == data->collectibles)
	{
		mlx_put_image_to_window(data->mlx, data->win, data->img_entrence.img_ptr,
			data->exit_x * IMG_SIZE , data->exit_y * IMG_SIZE);
	}
}
