/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:31:39 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/23 19:37:18 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	point_is_wall(t_data *data, double p_x, double p_y)
{
	char	**map;
	int		i;
	int		j;

	map = data->map;
	j = (p_x / TILE_SIZE);
	i = (p_y / TILE_SIZE);
	if (!map[i] || !map[i][j])
		return (1);
	if (map[i][j] == '1')
		return (1);
	return (0);
}

int	in_space(t_data *data)
{
	int	ittr;

	ittr = -1;
	while (ittr < 2)
	{
		if (point_is_wall(data, data->p_x + ittr, data->p_y))
			return (0);
		ittr++;
	}
	ittr = -1;
	while (ittr < 2)
	{
		if (point_is_wall(data, data->p_x, data->p_y + ittr))
			return (0);
		ittr++;
	}
	return (1);
}

void	normalize_angle(t_data *data)
{
	double	two_pi;

	two_pi = 2.0 * M_PI;
	data->rot_angle = fmod(data->rot_angle, two_pi);
	if (data->rot_angle <= 0)
		data->rot_angle += two_pi;
}

double	normalized_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int	has_wall(t_data *data, double x, double y)
{
	char	**map;
	int		i;
	int		j;

	map = data->map;
	if (x < 0 || y < 0)
		return (0);
	i = (int)(x / TILE_SIZE);
	j = (int)(y / TILE_SIZE);
	if (!(j > 0 && j * TILE_SIZE < data->h_map && i > 0
			&& i < (int)ft_strlen(map[j])) || map[j][i] == '1')
		return (1);
	return (0);
}
