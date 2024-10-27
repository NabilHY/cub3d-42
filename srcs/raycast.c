/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:05:57 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/23 19:37:18 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_direction(t_data *data)
{
	if (data->rot_angle > 0 && data->rot_angle < M_PI)
		data->v_dire = UP;
	else
		data->v_dire = DOWN;
	if ((data->rot_angle < 0.5 * M_PI) || (data->rot_angle > 1.5 * M_PI))
		data->h_dire = RIGHT;
	else
		data->h_dire = LEFT;
}

void	render_wall(t_data *data, int column, double fov)
{
	t_vline	coors;

	coors.projection_plane_distance = WIDTH / (2 * tan(fov / 2));
	coors.wall_height = (TILE_SIZE / data->distance)
		* coors.projection_plane_distance;
	coors.y_begin = (int)((HEIGHT / 2) - (coors.wall_height / 2));
	coors.y_end = (int)((HEIGHT / 2) + (coors.wall_height / 2));
	if (!data->vertical_inter)
	{
		if (data->ray_v_dire == UP)
			draw_vertical_line(data, column, &coors, data->texture_no);
		else
			draw_vertical_line(data, column, &coors, data->texture_so);
		return ;
	}
	if (data->ray_h_dire == LEFT)
		draw_vertical_line(data, column, &coors, data->texture_we);
	else
		draw_vertical_line(data, column, &coors, data->texture_ea);
}

void	draw_vertical_line(t_data *data, int x, t_vline *coors,
		mlx_texture_t *texture)
{
	int		y;
	double	texture_y;
	double	texture_pos;
	double	texture_x;

	if (!data || !data->view || !texture)
		return ;
	if (!data->vertical_inter)
		texture_x = fmod(data->p_x1, TILE_SIZE) / TILE_SIZE * texture->width;
	else
		texture_x = fmod(data->p_y1, TILE_SIZE) / TILE_SIZE * texture->width;
	texture_pos = 0.0;
	y = coors->y_begin;
	x = WIDTH - x - 1;
	while (y++ <= coors->y_end)
	{
		texture_y = (int)texture_pos % texture->height;
		if (y >= 0 && y < HEIGHT)
			mlx_put_pixel(data->view, x, y, get_pixel_color(texture,
					(int)texture_x, (int)texture_y));
		texture_pos += (double)texture->height / (coors->y_end
				- coors->y_begin);
	}
}

void	cast_rays(t_data *data)
{
	double	angle_increment;
	int		column;
	double	fov;
	double	half_fov;
	double	angle_offset;

	fov = data->p_radius * (M_PI / 180);
	half_fov = fov / 2;
	angle_offset = fov / (WIDTH - 1);
	angle_increment = fov / WIDTH;
	data->ray_angle = data->rot_angle + (fov / 2);
	column = 0;
	while (column < WIDTH)
	{
		data->ray_angle = normalized_angle(data->rot_angle - half_fov + (column
					* angle_offset));
		update_dire(data, data->ray_angle);
		set_intersections(data, data->ray_angle);
		render_wall(data, column, fov);
		data->ray_angle += angle_increment;
		column++;
	}
}
