/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:05:57 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/13 13:09:22 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	render_wall(t_data *data, int column, double fov)
{
	double	wall_height;
	double	projection_plane_distance;
	double	y_begin;
	double	y_end;

	projection_plane_distance = WIDTH / (2 * tan(fov / 2));
	wall_height = (TILE_SIZE / data->distance) * projection_plane_distance;
	y_begin = (HEIGHT / 2) - (wall_height / 2);
	y_end = (HEIGHT / 2) + (wall_height / 2);
	if (!data->vertical_inter)
	{
		if (data->ray_v_dire == UP)
			draw_vertical_line(data, column, (int)y_begin, (int)y_end,
				data->textureNO);
		else
			draw_vertical_line(data, column, (int)y_begin, (int)y_end,
				data->textureSO);
		return ;
	}
	if (data->ray_h_dire == LEFT)
		draw_vertical_line(data, column, (int)y_begin, (int)y_end,
			data->textureWE);
	else
		draw_vertical_line(data, column, (int)y_begin, (int)y_end,
			data->textureEA);
}

void	draw_vertical_line(t_data *data, int x, int y_start, int y_end,
		mlx_texture_t *texture)
{
	int			y;
	double		texture_y;
	double		step;
	double		texture_pos;
	double		texture_x;
	uint32_t	color;

	if (!data || !data->view || !texture)
		return ;
	if (!data->vertical_inter)
		texture_x = fmod(data->p_x1, TILE_SIZE) / TILE_SIZE * texture->width;
	else
		texture_x = fmod(data->p_y1, TILE_SIZE) / TILE_SIZE * texture->width;
	step = (double)texture->height / (y_end - y_start);
	texture_pos = 0.0;
	y = y_start;
	x = WIDTH - x - 1;
	while (y++ <= y_end)
	{
		texture_y = (int)texture_pos % texture->height;
		if (y >= 0 && y < HEIGHT)
		{
			color = get_pixel_color(texture, (int)texture_x, (int)texture_y);
			mlx_put_pixel(data->view, x, y, color);
		}
		texture_pos += step;
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
