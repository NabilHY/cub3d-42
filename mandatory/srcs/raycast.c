/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:05:57 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/02 10:15:50 by nhayoun          ###   ########.fr       */
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
	//mlx_put_pixel(data->img, (int)data->p_x1, (int)data->p_y1, get_rgba(255, 0,
	//		0, 255));
}

void	sub_points(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
/*
void	draw_line_h(t_data *data, double distance)
{
	double	dx;
	double	dy;
	double	y;
	double	dir;
	double	p;
	int		i;

	i = 0;
	if (data->p_x > data->p_x1)
	{
		sub_points(&data->p_x, &data->p_x1);
		sub_points(&data->p_y, &data->p_y1);
	}
	dx = data->p_x1 - data->p_x;
	dy = data->p_y1 - data->p_y;
	if (dy < 0)
		dir = -1;
	else
		dir = 1;
	if (dx != 0)
	{
		y = data->p_y;
		p = 2 * dy - dx;
		while (i < dx + 1)
		{
			mlx_put_pixel(data->img, data->p_x + i, y, get_rgba(255, 0, 0,
					255));
			if (p >= 0)
			{
				y += dir;
				p -= 2 * dx;
			}
			p += 2 * dy;
			i++;
		}
	}
}

void	draw_line_v(t_data *data, double distance)
{
	double	dx;
	double	dy;
	double	x;
	double	dir;
	double	p;
	int		i;

	i = 0;
	if (data->p_y > data->p_y1)
	{
		sub_points(&data->p_x, &data->p_x1);
		sub_points(&data->p_y, &data->p_y1);
	}
	dx = data->p_x1 - data->p_x;
	dy = data->p_y1 - data->p_y;
	if (dx < 0)
		dir = -1;
	else
		dir = 1;
	if (dy != 0)
	{
		x = data->p_x;
		p = 2 * dx - dy;
		while (i < dy + 1)
		{
			mlx_put_pixel(data->img, x, data->p_y + i, get_rgba(255, 0, 0,
					255));
			if (p >= 0)
			{
				x += dir;
				p -= 2 * dy;
			}
			p += 2 * dx;
			i++;
		}
	}
}

void	draw_line(t_data *data, double distance)
{
	if (fabs(data->p_x1 - data->p_x) > fabs(data->p_y1 - data->p_y))
	{
		draw_line_h(data, distance);
		printf("Player pos_x: %f pos_y: %f\n", data->p_x1, data->p_y1);
		printf("horizontal\n");
	}
	else
	{
		draw_line_v(data, distance);
		printf("Player pos_x: %f pos_y: %f\n", data->p_x, data->p_y);
		printf("vartical\n");
	}
}
*/