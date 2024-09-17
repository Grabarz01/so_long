/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:11:39 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/17 14:26:34 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int ft_close(t_data *data)
{
	ft_putstr_fd("Closing the window...\n", 1);
	ft_free_everything(data);
	exit(0);
}
void ft_hooks(t_data *data)
{
	mlx_hook(data->win, 2, (1L << 0), ft_change_pos, data);
	mlx_hook(data->win, 17, (1L << 0), ft_close, data);
}