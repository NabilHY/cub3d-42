/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:47:16 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/23 19:37:18 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
