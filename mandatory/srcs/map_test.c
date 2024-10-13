/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_test.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 11:17:29 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/13 16:47:43 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void something(t_data *data, int *i, int j)
{
	while (data->file[(*i)])
	{
		j = 0;
		while (data->file[(*i)][j])
		{
			if (data->file[(*i)][j] == ' ')
				j++;
			else
				break ;
		}
		if (data->file[(*i)][j] == '\0')
			(*i)++;
		else
			break ;
	}
}

int	copy_map(t_data *data, int i, int j)
{
	int	l;
	int	max;

	something(data,&i,j);
	j = i;
	while (data->file[i])
		i++;
	data->map = malloc(sizeof(char *) * (i - j + 1));
	l = 0;
	while (data->file[j])
	{
		data->map[l++] = ft_strdup(data->file[j]);
		j++;
	}
	data->map[l] = NULL;
	max = 0;
	i = -1;
	while (data->map[++i])
	{
		if (ft_strlen(data->map[i]) > max)
			max = ft_strlen(data->map[i]);
	}
	return (data->w_map = max, data->h_map = l, 0);
}

void	flood_fill(t_data *data, char ***copy, int x, int y, int *error)
{
	if (x > data->w_map || x < 0 || y > data->h_map || y < 0)
		return ;
	else if (x == data->w_map - 1 || x == 0 || y == data->h_map - 1 || y == 0)
	{
		if ((*copy)[y][x] == ' ' || (*copy)[y][x] == '0')
			*error = 1;
		return ;
	}
	if ((*copy)[y][x] == '1')
		return ;
	if ((*copy)[y][x] == ' ' || (*copy)[y][x] == '\0')
	{
		*error = 1;
		return ;
	}
	(*copy)[y][x] = '1';
	flood_fill(data, copy, x + 1, y, error);
	flood_fill(data, copy, x - 1, y, error);
	flood_fill(data, copy, x, y + 1, error);
	flood_fill(data, copy, x, y - 1, error);
}

int	another_function(char **copy, int *error, int height)
{
	int	i;
	int	j;
	int	line_len;

	i = 0;
	while (copy[i])
	{
		j = 0;
		line_len = ft_strlen(copy[i]);
		while (copy[i][j])
		{
			if (copy[i][j] == ' ')
			{
				if (i > 0 && i < height - 1)
				{
					if (copy[i - 1][j] == '0')
						return (*error = 1, 1);
					else if (copy[i + 1][j] == '0')
						return (*error = 1, 1);
					if (j == 0)
					{
						if (copy[i][j + 1] == '0')
							return (*error = 1, 1);
					}
					else if (j == line_len)
					{
						if (copy[i][j - 1] == '0')
							return (*error = 1, 1);
					}
					else
					{
						if (copy[i][j + 1] == '0')
							return (*error = 1, 1);
						else if (copy[i][j - 1] == '0')
							return (*error = 1, 1);
					}
				}
				else if (i == 0)
				{
					if (copy[i + 1][j] == '0')
						return (*error = 1, 1);
					if (j == 0)
					{
						if (copy[i][j + 1] == '0')
							return (*error = 1, 1);
					}
					else if (j == line_len)
					{
						if (copy[i][j - 1] == '0')
							return (*error = 1, 1);
					}
					else
					{
						if (copy[i][j + 1] == '0')
							return (*error = 1, 1);
						else if (copy[i][j - 1] == '0')
							return (*error = 1, 1);
					}
				}
				else
				{
					if (copy[i - 1][j] == '0')
						return (*error = 1, 1);
					if (j == 0)
					{
						if (copy[i][j + 1] == '0')
							return (*error = 1, 1);
					}
					else if (j == line_len)
					{

						if (copy[i][j - 1] == '0')
							return (*error = 1, 1);
					}
					else
					{
						if (copy[i][j + 1] == '0')
							return (*error = 1, 1);
						else if (copy[i][j - 1] == '0')
							return (*error = 1, 1);
					}
				}
			}
			j++;
		}
		i++;
	}
	return 0;
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
	return 0;
}

void get_player_position(t_data *data,int i, int j)
{
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
				data->p_x = j;
				data->p_y = i;
			j++;
		}
		i++;
	}
}

int	parsing_test(t_data *data, int i, int j, int error)
{
	char	**copy;

	get_player_position(data,0,0);
	copy = malloc(sizeof(char *) * (data->h_map + 1));
	while (i < data->h_map)
	{
		copy[i] = ft_strdup(data->map[i]);
		i++;
	}
	copy[i] = NULL;
	i = -1;
	while (copy[++i])
	{
		j = 0;
		while (copy[i][j] && copy[i][j] == ' ')
			j++;
		if (copy[i][j] == '\0')
			return (printf("found empty line\n"), free_2d(copy), 1);
	}
	flood_fill(data, &copy, data->p_x, data->p_y, &error);
	if (another_function(copy, &error, data->h_map) == 1)
		return (printf("fucked up map\n"), free_2d(copy), 1);
	if (borders_check(copy, &error, data->h_map, -1) == 1 || error == 1)
		return (printf("another fucked up map\n"), free_2d(copy), 1);
	return (free_2d(copy), 0);
}

int	test_map_validity(char *filename, t_data *data, t_map_data *x)
{
	int i = 0;
	//pretests
	if (ext_test(filename) == 0)
	{
		printf("failed in file extension\n");
		return 1;
	}
	if (file_existance(filename) == 1)
	{
		printf("failed in opening file\n");
		return 1;
	}
	copy_file(filename, data,0,0);
	//end of pretests
	//map_textures_tests
	if (test_textures(data, &i, x, 0) == 1)
	{
		printf("texrure test\n");
		return 1;
	}
	//end of map_textures_tests
	copy_map(data, i, 0);
	if (parsing_test(data,0,0,0) == 1)
		return 1;
	return 0;
}