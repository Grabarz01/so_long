/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validators.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:18:05 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/17 14:44:04 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_element_access(char **map_copy, int x, int y, t_elements *access)
{
	char *element;

	element = &(map_copy[y][x]);
	if (*element == '1')
		return;
	else if (*element == 'E')
	{
		*element = '1';
		access->exit++;
		return;
	}
	else if (*element == 'C')
	{
		*element = '1';
		access->colectibles++;
	}
	else if (*element == '0')
		*element = '1';
	else if (*element == 'P')
		*element = '1';
	ft_element_access(map_copy, x + 1, y, access);
	ft_element_access(map_copy, x, y + 1, access);
	ft_element_access(map_copy, x, y - 1, access);
	ft_element_access(map_copy, x - 1, y, access);
	return;
}

void ft_walls(t_data *data)
{
	int n;

	n = -1;
	while(data->map[0] && data->map[0][++n])
		if(data->map[0][n] != '1')
			ft_error_manager(6);
	n = -1;
	while(data->map[++n] && data->map[n][0])
		if(data->map[n][0] != '1')
			ft_error_manager(6);
	n = -1;
	while(data->map[++n] && data->map[n][data->map_width - 1])
		if(data->map[n][data->map_width - 1] != '1')
			ft_error_manager(6);
	n = -1;
	while(data->map[data->map_height - 1] && data->map[data->map_height - 1][++n])
		if(data->map[data->map_height - 1][n] != '1')
			ft_error_manager(6);
}
int	ft_count_elements(char element, t_data *data)
{
	static int player;
	static int exit;
	
	if (element == 'P')
		player++;
	if (element == 'E')
		exit++;
	if (element == 'C')
		data->collectibles++;
	if(exit > 1 || player > 1)
	{
		ft_free_split(data->map);
		ft_error_manager(3);
	}
	if(data->collectibles >= 1 && exit == 1 && player == 1)
		return(1);
	return(0);
}

void	ft_elements(char **map, t_data *data, int n, int m)
{
	while(map[++m])
	{
		while(map[m][++n])
			{
				if (map[m][n] != 'E' && map[m][n] != 'P' && map[m][n] != '1'
				 	&& map[m][n] != '0' && map[m][n] != 'C')
				{
					ft_free_split(map);
					ft_error_manager(2);
				}
				if (map[m][n] == 'P' || map[m][n] == 'E' || map[m][n] == 'C')
					ft_count_elements(map[m][n], data); 
				if (map[m][n] == 'P')
					ft_starting_point(n, m, data);
				if (map[m][n] == 'E')
					ft_exit_point(n, m, data);
			}
		n = 0;	
	}
	if (ft_count_elements(0, data) != 1)
	{
		ft_free_split(map);
		ft_error_manager(1);
	}
}

void	ft_get_size(int fd, t_data *data)
{
	char *buff;

	while(1)
	{
		buff = get_next_line(fd);
		if (buff == NULL)
			break;
		if (++(data->map_height) == 1)
			data->map_width = ft_strlen(buff);
		else if (data->map_width == (int)ft_strlen(buff) &&
		 	buff[data->map_width - 1] != '\n')
			{
				free(buff);
				ft_error_manager(5);
			}
		else if (data->map_width == (int)(ft_strlen(buff)) + 1)
			ft_check_line(buff, data);
		else if (data->map_width != (int)ft_strlen(buff))
		{
			free(buff);
			ft_error_manager(5);
		}
		free(buff);
	}
}