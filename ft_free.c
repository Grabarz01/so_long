/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:14:03 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/17 15:46:43 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_free_split(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
	{
		free(args[i]);
	}
	free(args);
}

void	ft_free_imgs(t_data *data)
{
	if (data->img_back.img_ptr)
		mlx_destroy_image(data->mlx, data->img_back.img_ptr);
	if (data->img_front.img_ptr)
		mlx_destroy_image(data->mlx, data->img_front.img_ptr);
	if (data->img_left.img_ptr)
		mlx_destroy_image(data->mlx, data->img_left.img_ptr);
	if (data->img_right.img_ptr)
		mlx_destroy_image(data->mlx, data->img_right.img_ptr);
	if (data->img_exit.img_ptr)
		mlx_destroy_image(data->mlx, data->img_exit.img_ptr);
	if (data->img_entrence.img_ptr)
		mlx_destroy_image(data->mlx, data->img_entrence.img_ptr);
	if (data->img_wall.img_ptr)
		mlx_destroy_image(data->mlx, data->img_wall.img_ptr);
	if (data->img_collectible.img_ptr)
		mlx_destroy_image(data->mlx, data->img_collectible.img_ptr);
	if (data->img_floor.img_ptr)
		mlx_destroy_image(data->mlx, data->img_floor.img_ptr);
}

void	ft_free_everything(t_data *data)
{
	ft_free_imgs(data);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	ft_free_split(data->map);
}
