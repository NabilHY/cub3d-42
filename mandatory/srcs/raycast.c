/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:05:57 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/11 16:27:47 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	end_point(t_data *data, double rad)
{
	double	dx;
	double	dy;
	double	distance;

	distance = 1000000;
	// Convert angle to radian deg * rot_angle
	// Endpoint coordinates
	// Change in x
	dx = distance * cos(rad);
	dy = distance * (sin(rad) * -1);
	data->p_x1 = data->p_x + dx;
	data->p_y1 = data->p_y + dy;
	// mlx_put_pixel(data->img, (int)data->p_x1, (int)data->p_y1, get_rgba(255,
	// 0,
	//		0, 255));
}

double	calc_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

void	sub_points(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
/*

void	cast(t_data *data, double angle)
{
	int		h_wall;
	int		v_wall;
	double	h_wall_x;
	double	h_wall_y;
	double	v_wall_x;
	double	v_wall_y;
	double	x_inter;
	double	y_inter;
	double	next_x_h_inter;
	double	next_y_h_inter;
	double	next_x_v_inter;
	double	next_y_v_inter;
	double	xa;
	double	ya;
	double	horizontal_distance;
	double	vertical_distance;
	double	wall_hit_x;
	double	wall_hit_y;

	// HIT BOOS
	// WALL HIT COORDINATES
	// INTERSATION WITH TILE
	// NEXT INTERSACTION POINT
	// DISTANCES INCREMENTS
	// Boolean Values
	h_wall = 0;
	v_wall = 0;
	// Position of tile intersatcion
	h_wall_x = 0;
	h_wall_y = 0;
	v_wall_x = 0;
	v_wall_y = 0;
	xa = 0;
	ya = 0;

	wall_hit_x = 0;
	wall_hit_y = 0;
	// Horizontal checking
	if (data->v_dire == UP)
		y_inter = (floor(data->p_y / TILE_SIZE) * TILE_SIZE) - 1;
	else if (data->v_dire == DOWN)
		y_inter = (floor(data->p_y / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
	x_inter = data->p_x + ((y_inter - data->p_y) / tan(angle));
	next_x_h_inter = x_inter;
	next_y_h_inter = y_inter;
	if (data->v_dire == UP)
		ya = TILE_SIZE * -1;
	else
		ya = TILE_SIZE;
	xa = ya / tan(angle);
	while ((next_x_h_inter <= WIDTH && next_x_h_inter >= 0)
		&& (next_y_h_inter <= HEIGHT && next_y_h_inter >= 0))
	{
		if (has_wall(data, next_x_h_inter, next_y_h_inter))
		{
			h_wall = 1;
			h_wall_x = next_x_h_inter;
			h_wall_y = next_y_h_inter;
			break ;
		}
		else
		{
			next_x_h_inter += xa;
			next_y_h_inter += ya;
		}
	}
	// Vertical Checking
	if (data->h_dire == RIGHT)
		x_inter = floor((data->p_x / TILE_SIZE) * TILE_SIZE) + TILE_SIZE;
	else if (data->h_dire == LEFT)
		x_inter = floor((data->p_x / TILE_SIZE) * TILE_SIZE) - 1;
	y_inter = data->p_y + (x_inter - data->p_x) * tan(data->rot_angle);
	next_x_v_inter = x_inter;
	next_y_v_inter = y_inter;
	if (data->h_dire == RIGHT)
		xa = TILE_SIZE;
	else if (data->v_dire == LEFT)
		xa = TILE_SIZE * -1;
	ya = xa * tan(data->rot_angle);
	while ((next_x_v_inter <= WIDTH && next_x_v_inter >= 0)
		&& (next_y_v_inter <= HEIGHT && next_y_v_inter >= 0))
	{
		if (has_wall(data, next_x_v_inter, next_y_v_inter))
		{
			v_wall = 1;
			v_wall_x = next_x_v_inter;
			v_wall_y = next_y_v_inter;
			break ;
		}
		else
		{
			next_x_v_inter += xa;
			next_y_v_inter += ya;
		}
	}
	// Distance Calculation
	horizontal_distance = 0;
	vertical_distance = 0;
	if (h_wall)
		horizontal_distance = calc_distance(data->p_x, data->p_y, h_wall_x,
				h_wall_y);
	else
		horizontal_distance = 10000;
	if (v_wall)
		vertical_distance = calc_distance(data->p_x, data->p_y, v_wall_x,
				v_wall_y);
	else
		vertical_distance = 10000;
	//if (horizontal_distance < vertical_distance)
	//{
		wall_hit_x = h_wall_x;
		wall_hit_y = h_wall_y;
	//}
	//else
	//{
	//	wall_hit_x = v_wall_x;
	//	wall_hit_y = v_wall_y;
	//}
	data->p_x1 = wall_hit_x;
	data->p_y1 = wall_hit_y;
}
*/