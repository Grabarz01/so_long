/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_renders.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:28:48 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/17 15:56:41 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_put_img(int x, int y, t_data *data)
{
	char	element;
	
	element = data->map[y][x];
	if (element == '1')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img_wall.img_ptr, x * IMG_SIZE, y * IMG_SIZE);
	if (element == '0')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img_floor.img_ptr, x * IMG_SIZE, y * IMG_SIZE);
	if (element == 'P')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img_front.img_ptr, x * IMG_SIZE, y * IMG_SIZE);
	if (element == 'E')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img_exit.img_ptr, x * IMG_SIZE, y * IMG_SIZE);
	if (element == 'C')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img_collectible.img_ptr, x * IMG_SIZE, y * IMG_SIZE);
}

void	ft_render_map(t_data *data)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	while (++x < data->map_width )
	{
		
		while (++y < data->map_height)
			ft_put_img(x, y, data);
		y = -1;
	}
		
}

void	ft_init_imgs(char *path, t_data *data, t_img *img)
{
	img->img_ptr = mlx_xpm_file_to_image(data->mlx, path, &img->width, &img->height);
	if (!img->img_ptr)
	{
		ft_free_everything(data);
		ft_error_message("Error\nCannot upload one of the imgs", 1);
	}
}

void	ft_all_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		ft_free_split(data->map);
		ft_error_message("Error\nIssue occured while connecting to the mlx\n", 1);
	}	
	data->win = mlx_new_window(data->mlx, IMG_SIZE * data->map_width, IMG_SIZE * data->map_height, "so_long");
	if (!data->win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		ft_free_split(data->map);
		ft_error_message("Error\n cannot creat the window\n", 1);
	}
	ft_init_imgs(WALL_IMG, data, &data->img_wall);
	ft_init_imgs(FLOOR_IMG, data, &data->img_floor);
	ft_init_imgs(BACK_IMG, data, &data->img_back);
	ft_init_imgs(FRONT_IMG, data, &data->img_front);
	ft_init_imgs(LEFT_IMG, data, &data->img_left);
	ft_init_imgs(RIGHT_IMG, data, &data->img_right);
	ft_init_imgs(COLLECTIBLE_IMG, data, &data->img_collectible);
	ft_init_imgs(EXIT_IMG, data, &data->img_exit);
	ft_init_imgs(ENTRANCE_IMG, data, &data->img_entrence);
}
