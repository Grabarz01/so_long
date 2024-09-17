/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrabows <fgrabows@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:05:02 by fgrabows          #+#    #+#             */
/*   Updated: 2024/09/17 12:02:35 by fgrabows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_render_map(t_data *data);
void	ft_free_everything(t_data *data);
void	ft_all_init(t_data *data);
void	ft_init_imgs(char *path, t_data *data, t_img *img);
void	ft_input_checker(int argc, char **argv);
void	ft_map_checker(char *map, t_data *data);
void	ft_get_size(int fd, t_data *data);
void	ft_check_map(int fd, t_data *data);
void ft_print_split(char **str);
void ft_allocate_map_memory(t_data *data);
void ft_set_map(int fd, t_data *data);
void	ft_elements(char **map, t_data *data, int n, int m);
int	ft_count_elements(char element, t_data *data);
void ft_walls(t_data *data);
char 	**ft_map_copy(t_data *data);
void ft_element_access(char **map_copy, int x, int y, t_elements *access);
void ft_starting_point(int x, int y, t_data *data);
void ft_error_manager(int x);
void ft_error_message(char *str, int num);
void ft_set_ptrs(t_data *data);
void	ft_free_split(char **args);

void	ft_free_imgs(t_data *data);







//  int	ft_empty_arg(char *argv)
// {
// 	int	i;

// 	i = 0;
// 	while(argv[i])
// 	{
// 		while (argv[i] && (argv[i] == ' ' || argv[i] == '\t' || argv[i] == '\f'
// 			|| argv[i] == '\v' || argvvoid	ft_get_size(int fd, t_data *data)
// 			i++;
// 		if (!argv[i] || ft_strncmp(argv[i], ".bar", 5) == 0)
// 			break;
// 		return(0);
// 	}
// 	ft_putstr_fd("Error: empty argument", 2);
// 	exit(1);
// }

//exit is accessible
//there is only one exit
//there is only one player
//there is at least one collectible
//all collectibles are available
//only accept 0,1,P,E,C
//for the time of checking the possibility to access collectibles
	//we consider the exit the same as wall
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
void ft_error_message(char *str, int num)
{
	ft_putstr_fd(str,2);
	exit(num);
}

void ft_error_manager(int x)
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
void ft_starting_point(int x, int y, t_data *data)
{
	data->x_player = x;
	data->y_player = y;
}

void ft_element_access(char **map_copy, int x, int y, t_elements *access)
{
	char *element;

	element = &(map_copy[y][x]);
	if (*element == '1')//| posision.x > data->map_height - 1 || posision.y > data->map_width - 1 || posision.x)
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

void ft_exit_point (int x, int y, t_data *data)
{
	data->exit_x = x;
	data->exit_y = y;
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
void ft_print_split(char **str)
{
	int i;

	i=0;
	if(!str)
		return;
	while(str[i])
		printf("split args:%s\n",str[i++]);
}
void	ft_check_map(int fd, t_data *data)
{
	char **map_copy;
	t_elements access;
	
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
	if(access.colectibles != data->collectibles || access.exit != 1)
	{
		ft_free_split(data->map);
		ft_error_manager(7);
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


void	ft_map_checker(char *map, t_data *data)
{
	int fd;
	int fd2;

	fd = open(map, O_RDONLY);
	if(fd < 0)
		ft_error_manager(0);
	data->map_height = 0;
	data->map_width = 0;
	ft_get_size(fd, data);
	if (data->map_height < 3 || data->map_width < 4) // with \n
		ft_error_manager(4);
	fd2 = open(map, O_RDONLY);
	if(fd2 < 0)
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
//rendering and this stuf
void	ft_init_imgs(char *path, t_data *data, t_img *img)
{
	img->img_ptr = mlx_xpm_file_to_image(data->mlx, path, &img->width, &img->height);
	if(!img->img_ptr)
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
		ft_error_message("Error\nIssue occured while connecting to the mlx\n",1);
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
void	ft_free_imgs(t_data *data)
{
	if(data->img_back.img_ptr)
		mlx_destroy_image(data->mlx, data->img_back.img_ptr);
	if(data->img_front.img_ptr)
		mlx_destroy_image(data->mlx, data->img_front.img_ptr);
	if(data->img_left.img_ptr)
		mlx_destroy_image(data->mlx, data->img_left.img_ptr);
	if(data->img_right.img_ptr)
		mlx_destroy_image(data->mlx, data->img_right.img_ptr);
	if(data->img_exit.img_ptr)
		mlx_destroy_image(data->mlx, data->img_exit.img_ptr);
	if(data->img_entrence.img_ptr)
		mlx_destroy_image(data->mlx, data->img_entrence.img_ptr);
	if(data->img_wall.img_ptr)
		mlx_destroy_image(data->mlx, data->img_wall.img_ptr);
	if(data->img_collectible.img_ptr)
		mlx_destroy_image(data->mlx, data->img_collectible.img_ptr);
	if(data->img_floor.img_ptr)
		mlx_destroy_image(data->mlx, data->img_floor.img_ptr);
}
void	ft_free_everything(t_data *data)
{
	ft_free_imgs(data);
	if(data->win)
		mlx_destroy_window(data->mlx, data->win);
	if(data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	ft_free_split(data->map);

}

void ft_put_img(int x, int y, t_data *data)
{
	char element;
	
	element = data->map[y][x];
	if(element == '1')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img_wall.img_ptr, x * IMG_SIZE, y * IMG_SIZE);
	if(element == '0')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img_floor.img_ptr, x * IMG_SIZE, y * IMG_SIZE);
	if(element == 'P')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img_front.img_ptr, x * IMG_SIZE, y * IMG_SIZE);
	if(element == 'E')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img_exit.img_ptr, x * IMG_SIZE, y * IMG_SIZE);
	if(element == 'C')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img_collectible.img_ptr, x * IMG_SIZE, y * IMG_SIZE);
	
		
}
void	ft_render_map(t_data *data)
{
	int x;
	int y;

	x = -1;
	y = -1;
	while(++x < data->map_width )
	{
		
		while(++y < data->map_height)
			ft_put_img(x, y, data);
		y = -1;
	}
		
}

int ft_check_next_object(int x, int y, t_data *data)
{
	char element;

	element = data->map[y][x]; 
	if (element == '1')
		return (0);
	if (element == 'E')
	{
		if (data->collected == data->collectibles)
		{
			return (1);
		}
		return (0);
	
	}
	return(1);
}
void ft_print_moves(int moves)
{
	if(moves == 1)
		ft_putstr_fd("You made 1 move\n", 1);
	else
	{
		ft_putstr_fd("You made ", 1);
		ft_putnbr_fd(moves , 1);
		ft_putstr_fd(" moves.\n", 1);
	}
}
void ft_win(int x, int y, t_data *data)
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
int main(int argc, char **argv)
{
	t_data data;
	
	ft_input_checker(argc, argv);
	ft_map_checker(argv[1], &data);
	ft_set_ptrs(&data);
	ft_all_init(&data);
	ft_render_map(&data);
	ft_hooks(&data);
	mlx_loop(data.mlx);

	
}
