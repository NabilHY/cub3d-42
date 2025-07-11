/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:17:29 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/29 18:03:57 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	flood_fill(t_data *data, int x, int y, int *error)
{
	if (x > data->w_map || x < 0 || y > data->h_map || y < 0)
		return ;
	else if (x == data->w_map - 1 || x == 0 || y == data->h_map - 1 || y == 0)
	{
		if (data->copy[y][x] == ' ' || data->copy[y][x] == '0')
		{
			*error = 1;
			return ;
		}
	}
	if (data->copy[y][x] == '1')
		return ;
	if (data->copy[y][x] == ' ' || data->copy[y][x] == '\0')
	{
		*error = 1;
		return ;
	}
	data->copy[y][x] = '1';
	flood_fill(data, x + 1, y, error);
	flood_fill(data, x - 1, y, error);
	flood_fill(data, x, y + 1, error);
	flood_fill(data, x, y - 1, error);
}

int	borders_check(char **copy, int *error, int height, int i)
{
	while (copy[0][++i])
	{
		if (copy[0][i] == '0')
			return (*error = 1, 1);
	}
	i = -1;
	while (copy[height - 1][++i])
	{
		if (copy[height - 1][i] == '0')
			return (*error = 1, 1);
	}
	i = -1;
	while (copy[++i])
	{
		if (copy[i][0] == '0')
			return (*error = 1, 1);
	}
	i = 0;
	while (copy[i])
	{
		if (copy[i][ft_strlen(copy[i]) - 1] == '0')
			return (*error = 1, 1);
		i++;
	}
	return (0);
}

void	get_player_position(t_data *data, int i, int j, int *error)
{
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
			{
				data->p_x = j;
				data->p_y = i;
			}
			j++;
		}
		i++;
	}
	if ((int)data->p_y == data->h_map - 1 || (int)data->p_y == 0 
		|| (int)data->p_x == 0 
		|| (int)data->p_x == ft_strlen(data->map[(int)data->p_y]) - 1)
	{
		printf("Error\nError in player position\n");
		*error = 1;
	}
}

int	parsing_test(t_data *data, int i, int j, int error)
{
	get_player_position(data, 0, 0, &error);
	if (error == 1)
		return (1);
	data->copy = malloc(sizeof(char *) * (data->h_map + 1));
	if (!data->copy)
		return (printf("Error\nMalloc error\n"), 1);
	clone_map(data, -1);
	i = -1;
	while (data->copy[++i])
	{
		j = 0;
		while (data->copy[i][j] && data->copy[i][j] == ' ')
			j++;
		if (data->copy[i][j] == '\0')
			return (printf("Error\nFound empty line\n"), free_2d(data->copy), 1);
	}
	flood_fill(data, data->p_x, data->p_y, &error);
	if (error == 1)
		return (printf("Error\nFucked up map\n"), free_2d(data->copy), 1);
	if (another_function(data->copy, &error, data->h_map, -1) == 1)
		return (printf("Error\nFucked up map\n"), free_2d(data->copy), 1);
	if (borders_check(data->copy, &error, data->h_map, -1) == 1 || error == 1)
		return (printf("Error\nAnother fucked up map\n"), free_2d(data->copy), 1);
	return (free_2d(data->copy), 0);
}

int	test_map_validity(char *filename, t_data *data, t_map_data *x)
{
	int	i;

	i = 0;
	if (ext_test(filename) == 0)
		return (printf("Error\nFailed in file extension\n"), 1);
	if (file_existance(filename) == 1)
		return (printf("Error\nfailed in opening file\n"), 1);
	copy_file(filename, data, 0, 0);
	if (test_textures(data, &i, x, 0) == 1)
	{
		free_2d(data->file);
		(free(x->ea.str), free(x->we.str), free(x->so.str), free(x->no.str));
		(free(x->ceil.str), free(x->floor.str));
		return (1);
	}
	copy_map(data, i, 0);
	if (parsing_test(data, -1, 0, 0) == 1)
		return (free_all(data, x), 1);
	return (0);
}
