/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:18:38 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/17 14:39:04 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "so_long.h"

char 	**ft_map_copy(t_data *data)
{
	char	**map_copy;
	int		n;

	n = -1;
	map_copy = malloc(sizeof(char *) * (data->map_height + 1));
	if (!map_copy)
	{
		ft_free_split(data->map);
		ft_error_manager(0);
	}
	while(++n < data->map_height)
	{
		map_copy[n] = ft_strdup(data->map[n]);
		if(!map_copy[n])
		{
			ft_free_split(map_copy);
			ft_free_split(data->map);
			ft_error_manager(0);
		}
	}
	map_copy[n] = NULL;
	return(map_copy);
}


void ft_set_map(int fd, t_data *data)
{
	char *buff;
	int n;

	n = 0;
	while(1)
	{
		buff = get_next_line(fd);
		if(!buff)
			break;
		ft_strlcpy(data->map[n], buff, data->map_width + 1);
		n++;
		free(buff);
	}
}

void 	ft_check_line(char *buff, t_data *data)
{
	char x;

	x = buff[data->map_width - 2];
	if (x == '1')
		return;
	else if (x == '0' || x =='P'|| x == 'E' || x =='C')
	{
		free(buff);
		ft_error_manager(6);
	}
	else
	{
		free(buff);
		ft_error_manager(5);
	}
}

void ft_allocate_map_memory(t_data *data)
{
	int n;

	data->map = malloc(sizeof(char *) * (data->map_height + 1));
	if (!(data->map))
		ft_error_manager(0);
	n = 0;
	while(n < data->map_height)
	{
		data->map[n] = malloc(sizeof(char) * data->map_width);
		if(!(data->map[n]))
		{
			ft_free_split(data->map);
			ft_error_manager(0);
		}
		n++;
	}
	data->map[n] = NULL;
	(data->map_width)--;
}