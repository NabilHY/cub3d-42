/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:33:42 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/23 19:37:18 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i * TILE_SIZE);
}

int	get_width(char **map)
{
	int	max;
	int	i;

	i = 0;
	max = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return ((int)max * TILE_SIZE);
}

void	player_position(t_data *data)
{
	static int	i;
	int			j;
	char		**map;

	map = data->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j++])
		{
			if (map[i][j])
			{
				if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S'
					|| map[i][j] == 'E')
				{
					data->p_x = j * TILE_SIZE;
					data->p_y = i * TILE_SIZE;
					data->p_direction = map[i][j];
				}
			}
		}
		i++;
	}
	data->p_x += TILE_SIZE / 2;
	data->p_y += TILE_SIZE / 2;
}

void	init_data(t_data *data, t_map_data x)
{
	data->texture_no = mlx_load_png(x.no.str);
	data->texture_we = mlx_load_png(x.we.str);
	data->texture_so = mlx_load_png(x.so.str);
	data->texture_ea = mlx_load_png(x.ea.str);
	player_position(data);
	if (data->p_direction == 'W')
		data->rot_angle = M_PI;
	if (data->p_direction == 'S')
		data->rot_angle = M_PI / 2 + M_PI;
	if (data->p_direction == 'E')
		data->rot_angle = 0;
	if (data->p_direction == 'N')
		data->rot_angle = M_PI / 2;
	data->h_map = get_height(data->map);
	data->w_map = get_width(data->map);
	data->p_radius = 60;
	data->move_speed = 4;
	data->accum = 0;
	data->rot_speed = 6 * (M_PI / 180);
	data->ceiling_color = get_rgba(x.ccolor[0], x.ccolor[1], x.ccolor[2], 255);
	data->floor_color = get_rgba(x.fcolor[0], x.fcolor[1], x.fcolor[2], 255);
	data->last_x = WIDTH / 2;
	set_direction(data);
}
