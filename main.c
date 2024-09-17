/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:05:02 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/17 15:51:53 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//exit is accessible
//there is only one exit
//there is only one player
//there is at least one collectible
//all collectibles are available
//only accept 0,1,P,E,C
//for the time of checking the possibility to access collectibles
	//we consider the exit the same as wall
void	ft_map_checker(char *map, t_data *data)
{
	int	fd;
	int	fd2;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		ft_error_manager(0);
	data->map_height = 0;
	data->map_width = 0;
	ft_get_size(fd, data);
	if (data->map_height < 3 || data->map_width < 4) // with \n
		ft_error_manager(4);
	fd2 = open(map, O_RDONLY);
	if (fd2 < 0)
	{
		ft_free_split(data->map);
		ft_error_manager(0);
	}
	close(fd);
	ft_check_map(fd2, data);
}

void	ft_input_checker(int argc, char **argv)
{
	int	n;

	if(argc != 2)
	{
		ft_putstr_fd("Error\nProgram accepts only one argument which should be map.ber\n", 2);
		exit(1);
	}
	n = ft_strlen(argv[1]);
	if (n < 5)
	{
		ft_putstr_fd("Error\nWrong argument\n", 2);
		exit(1);
	}
	if (ft_strncmp(&argv[1][n - 4], ".ber", 5) == 0 && argv[1][n - 5] == '/')
	{
		ft_putstr_fd("Error\nWrong argument\n", 2);
		exit(1);
	}
	if (ft_strncmp(&argv[1][n - 4], ".ber", 5) != 0)
	{
		ft_putstr_fd("Error\nWrong file extension\n", 2);
		exit(1);
	}
}
void	ft_check_map(int fd, t_data *data)
{
	char		**map_copy;
	t_elements	access;

	ft_allocate_map_memory(data);
	ft_set_map(fd, data);
	close(fd);
	data->collectibles = 0;
	ft_elements(data->map, data, -1, -1);
	ft_walls(data);
	map_copy = ft_map_copy(data);
	access.colectibles = 0;
	access.exit = 0;
	ft_element_access(map_copy, data->x_player, data->y_player, &access);
	ft_free_split(map_copy);
	if (access.colectibles != data->collectibles || access.exit != 1)
	{
		ft_free_split(data->map);
		ft_error_manager(7);
	}
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	ft_input_checker(argc, argv);
	ft_map_checker(argv[1], &data);
	ft_set_ptrs(&data);
	ft_all_init(&data);
	ft_render_map(&data);
	ft_hooks(&data);
	mlx_loop(data.mlx);
	ft_free_everything(&data);
}
