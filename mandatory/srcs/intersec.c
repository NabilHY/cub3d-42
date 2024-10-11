/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:10:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/10 16:47:10 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	first_hor_intersection(t_data *data, double deg)
{
	data->first_h_x = 0;
	data->first_h_y = 0;
	if (data->ray_v_dire == UP)
		data->first_h_y = floor(data->p_y / TILE_SIZE) * TILE_SIZE - 0.0000001;
	else
		data->first_h_y = floor(data->p_y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	data->first_h_x = (data->p_x + (data->first_h_y - data->p_y) / (tan(deg) *
				-1));
	return (0);
}

double	first_ver_intersection(t_data *data, double deg)
{
	if (data->ray_h_dire == RIGHT)
		data->first_v_x = floor(data->p_x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	else
		data->first_v_x = floor(data->p_x / TILE_SIZE) * TILE_SIZE - 0.0000001;
	data->first_v_y = data->p_y + (data->first_v_x - data->p_x) * (tan(deg) *
			-1);
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

double	hor_intersections(t_data *data, double deg, int *hit_wall)
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
	return (0);
}

double	ver_intersections(t_data *data, double deg, int *hit_wall)
{
	data->next_v_x = data->first_v_x;
	data->next_v_y = data->first_v_y;
	data->xa = 0;
	data->ya = 0;
	set_step(data, 1, deg);
	while (data->next_v_x <= data->w_map && data->next_v_x >= 0 && data->next_v_y <= data->h_map && data->next_v_y >= 0)
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

void	inters(t_data *data, double deg, double *hor_dist, double *ver_dist)
{
	int	found_hor_wall;
	int	found_ver_wall;

	found_hor_wall = 0;
	found_ver_wall = 0;
	first_hor_intersection(data, deg);
	first_ver_intersection(data, deg);
	hor_intersections(data, deg, &found_hor_wall);
	ver_intersections(data, deg, &found_ver_wall);
	if (found_hor_wall)
		*hor_dist = pethago_distance(data->hor_hit_x, data->p_x,
				data->hor_hit_y, data->p_y);
	else
		*hor_dist = 9999999.00;
	if (found_ver_wall)
		*ver_dist = pethago_distance(data->ver_hit_x, data->p_x,
				data->ver_hit_y, data->p_y);
	else
		*ver_dist = 99999999.00;
}

void	set_intersections(t_data *data, double deg)
{
	double	hor_dist;
	double	ver_dist;

	hor_dist = 0;
	ver_dist = 0;
	inters(data, deg, &hor_dist, &ver_dist);
	if (hor_dist < ver_dist)
	{
		data->vertical_inter = 0;
		data->p_x1 = data->hor_hit_x;
		data->p_y1 = data->hor_hit_y;
		data->distance = hor_dist;
	}
	else
	{
		data->vertical_inter = 1;
		data->p_x1 = data->ver_hit_x;
		data->p_y1 = data->ver_hit_y;
		data->distance = ver_dist;
	}
	data->distance *= cos(data->rot_angle - data->ray_angle);
}
