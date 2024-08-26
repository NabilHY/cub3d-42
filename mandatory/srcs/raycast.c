/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:05:57 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/26 16:30:57 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	end_point(t_data *data)
{
	double rad;
	double dx;
	double dy;
	double distance;

	distance = 40;
	// Convert angle to radian deg * rot_angle
	rad = data->rot_angle;
	// Endpoint coordinates
	// Change in x
	dx = distance * cos(rad);
	dy = distance * (sin(rad) * -1);
	printf("angle %f\n", data->rot_angle);
	printf("dx %f\n", dx);
	printf("dy %f\n", dy);
	data->p_x1 = data->p_x + dx;
	data->p_y1 = data->p_y + dy;
	mlx_put_pixel(data->img, (int)data->p_x1, (int)data->p_y1, get_rgba(255, 0, 0, 255));
}