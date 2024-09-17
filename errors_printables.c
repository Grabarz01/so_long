/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_printables.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:16:24 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/17 15:46:50 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_error_message(char *str, int num)
{
	ft_putstr_fd(str, 2);
	exit(num);
}

void	ft_error_manager(int x)
{
	if (x == 0)
	{
		ft_putstr_fd("Error\n", 2);
		perror(NULL);
	}
	else if (x == 1)
		ft_putstr_fd("Error\nNo collectibles on the map\n", 2);
	else if (x == 2)
		ft_putstr_fd("Error\nWrong map element(P, E, C, 1, 0)\n", 2);
	else if (x == 3)
		ft_putstr_fd("Error\nMore than one exit or starting positions\n", 2);
	else if (x == 4)
		ft_putstr_fd("Error\nInvalid map: map is too small\n",2 );
	else if (x == 5)
		ft_putstr_fd("Error\nInvalid map: this map is not rectangle\n", 2);
	else if (x == 6)
		ft_putstr_fd("Error\nInvalid map: the border of the map cosists of diffrent objects than walls\n", 2);
	else if (x == 7)
		ft_putstr_fd("Error\nInvalid map: At least one of collectibles or the exit is unacessible\n", 2);
	exit (1);
}

void	ft_print_moves(int moves)
{
	if (moves == 1)
		ft_putstr_fd("You made 1 move\n", 1);
	else
	{
		ft_putstr_fd("You made ", 1);
		ft_putnbr_fd(moves , 1);
		ft_putstr_fd(" moves.\n", 1);
	}
}
