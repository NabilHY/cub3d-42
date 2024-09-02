/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:02:58 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/02 18:11:15 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

double	scaling_value(double ival, double omin, double omax, double imax)
{
	return ((omax - omin) * (ival - 0) / (imax - 0) + omin);
}

void	draw_grid_lines(mlx_image_t *tile, int pos_x, int pos_y, int color)
{
	int	x;
	int	y;

	x = pos_x;
	y = pos_y;
	while (x < pos_x + TILE_SIZE - 1)
	{
		mlx_put_pixel(tile, x, pos_y, color);
		mlx_put_pixel(tile, x, pos_y + TILE_SIZE - 1, color);
		x++;
	}
	while (y < pos_y + TILE_SIZE - 1)
	{
		mlx_put_pixel(tile, pos_x, y, color);
		mlx_put_pixel(tile, pos_x + TILE_SIZE - 1, y, color);
		y++;
	}
}

void	fill_tile(mlx_image_t *tile, int color, int pos_x, int pos_y)
{
	int	x;
	int	y;

	x = 0;
	while (x < TILE_SIZE)
	{
		y = 0;
		while (y < TILE_SIZE)
		{
			mlx_put_pixel(tile, pos_x + x, pos_y + y, color);
			y++;
		}
		mlx_put_pixel(tile, pos_x + x, pos_y + y, color);
		mlx_put_pixel(tile, pos_x + x, pos_y + y, get_rgba(189, 195, 199, 255));
		x++;
	}
	draw_grid_lines(tile, pos_x, pos_y, get_rgba(189, 195, 199, 255));
}

void	draw_row(char *str, t_data *data, int y_pos)
{
	int	i;
	int	x_pos;

	i = 0;
	x_pos = 0;
	while (str[i])
	{
		if (str[i] == '1')
			fill_tile(data->img, get_rgba(0, 0, 0, 255), x_pos, y_pos);
		else if (str[i] == '0')
			fill_tile(data->img, get_rgba(255, 255, 255, 255), x_pos, y_pos);
		else if (str[i] == 'W' || str[i] == 'N' || str[i] == 'E'
			|| str[i] == 'S')
			fill_tile(data->img, get_rgba(255, 255, 255, 255), x_pos, y_pos);
		x_pos += TILE_SIZE;
		i++;
	}
}

void	spawn_player(t_data *data)
{
	mlx_put_pixel(data->img, data->p_x, data->p_y, get_rgba(0, 255, 0, 255));
}

void	map_render(t_data *data)
{
	int	i;
	int	y_pos;

	i = 0;
	y_pos = 0;
	while (data->map[i])
	{
		draw_row(data->map[i], data, y_pos);
		y_pos += TILE_SIZE;
		i++;
	}
}

double	cast_ray(t_data *data, double ray_deg)
{
	double	dx;
	double	dy;
	double	step;
	double	p_x;
	double	p_y;
	double	x_inc;
	double	y_inc;
	int		i;

	i = 0;
	p_x = data->p_x;
	p_y = data->p_y;
	dx = data->p_x1 - data->p_x;
	dy = data->p_y1 - data->p_y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	while (i <= step)
	{
		if (!ray_in_space(data, p_x, p_y) )
			break ;
		mlx_put_pixel(data->img, (int)(round(p_x)), (int)(round(p_y)),
			get_rgba(255, 0, 0, 255));
		p_x += x_inc;
		p_y += y_inc;
		i++;
	}
	return (0);
}

void	cast_rays(t_data *data)
{
	double	ray_deg;
	double	angle_increment;
	double	distance;
	int		column;
	double	fov;

	fov = data->p_radius * (M_PI / 180);
	angle_increment = fov / RES;
	ray_deg = data->rot_angle - (fov / 2);
	//ray_deg = data->rot_angle;
	//column = 0;
	while (column < RES)
	{
		end_point(data, ray_deg);
		cast_ray(data, ray_deg);
		ray_deg += angle_increment;
		//printf(" column: %d raydeg: %f\n", column, ray_deg);
		column++;
	}
}

void	draw_map(t_data *data)
{
	int x;
	int y_pos;
	int i;
	char **map;

	i = 0;
	x = 0;
	y_pos = 0;
	map = data->map;
	if (data->img)
		mlx_delete_image(data->mlx_ptr, data->img);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	map_render(data);
	spawn_player(data);
	cast_rays(data);
	// end_point(data);
	mlx_image_to_window(data->mlx_ptr, data->img, 0, 0);
}