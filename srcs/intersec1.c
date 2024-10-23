/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:10:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/23 19:37:18 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	first_hor_intersection(t_data *data, double deg)
{
	double	tang;

	data->first_h_x = 0;
	data->first_h_y = 0;
	if (data->ray_v_dire == UP)
		data->first_h_y = floor(data->p_y / TILE_SIZE) * TILE_SIZE - 0.0000001;
	else
		data->first_h_y = floor(data->p_y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	tang = tan(deg) * -1;
	data->first_h_x = (data->p_x + (data->first_h_y - data->p_y) / (tang));
	return (0);
}

double	first_ver_intersection(t_data *data, double deg)
{
	double	tang;

	if (data->ray_h_dire == RIGHT)
		data->first_v_x = floor(data->p_x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	else
		data->first_v_x = floor(data->p_x / TILE_SIZE) * TILE_SIZE - 0.0000001;
	tang = tan(deg) * -1;
	data->first_v_y = data->p_y + (data->first_v_x - data->p_x) * (tang);
	return (0);
}

void	set_step(t_data *data, int ver, double deg)
{
	if (!ver)
	{
		if (data->ray_v_dire == UP)
			data->ya = TILE_SIZE * -1;
		else if (data->ray_v_dire == DOWN)
			data->ya = TILE_SIZE;
		data->xa = data->ya / (tan(deg) * -1);
	}
	else
	{
		if (data->ray_h_dire == RIGHT)
			data->xa = TILE_SIZE;
		else
			data->xa = TILE_SIZE * -1;
		data->ya = data->xa * (tan(deg) * -1);
	}
}

void	hor_intersections(t_data *data, double deg, int *hit_wall)
{
	data->next_h_x = data->first_h_x;
	data->next_h_y = data->first_h_y;
	data->xa = 0;
	data->ya = 0;
	set_step(data, 0, deg);
	while (data->next_h_x <= data->w_map && data->next_h_x >= 0
		&& data->next_h_y <= data->h_map && data->next_h_y >= 0)
	{
		if (has_wall(data, data->next_h_x, data->next_h_y) || has_wall(data,
				data->next_h_x + 0.0000001, data->next_h_y) || has_wall(data,
				data->next_h_x, data->next_h_y + 0.0000001))
		{
			*hit_wall = 1;
			data->hor_hit_x = data->next_h_x;
			data->hor_hit_y = data->next_h_y;
			break ;
		}
		else
		{
			data->next_h_x += data->xa;
			data->next_h_y += data->ya;
		}
	}
}

void	ver_intersections(t_data *data, double deg, int *hit_wall)
{
	data->next_v_x = data->first_v_x;
	data->next_v_y = data->first_v_y;
	data->xa = 0;
	data->ya = 0;
	set_step(data, 1, deg);
	while (data->next_v_x <= data->w_map && data->next_v_x >= 0
		&& data->next_v_y <= data->h_map && data->next_v_y >= 0)
	{
		if (has_wall(data, data->next_v_x, data->next_v_y) || has_wall(data,
				data->next_v_x + 0.0000001, data->next_v_y) || has_wall(data,
				data->next_v_x, data->next_v_y + 0.0000001))
		{
			*hit_wall = 1;
			data->ver_hit_x = data->next_v_x;
			data->ver_hit_y = data->next_v_y;
			break ;
		}
		else
		{
			data->next_v_x += data->xa;
			data->next_v_y += data->ya;
		}
	}
}
