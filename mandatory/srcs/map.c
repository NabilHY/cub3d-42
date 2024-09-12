/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:02:58 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/12 21:18:11 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_point(t_data *data, int x, int y, int color);

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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
	if (!(j > 0 && j < data->h_map && i > 0 && i < (int)ft_strlen(map[j]))
		|| map[j][i] == '1')
		return (1);
	return (0);
}

double	row_len(t_data *data, double x)
{
	char	**map;
	int		i;

	map = data->map;
	if (x < 0)
		return (0);
	i = (int)(x / TILE_SIZE);
	return ((double)ft_strlen(map[i]) * TILE_SIZE);
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
			fill_tile(data->map_img, get_rgba(0, 0, 0, 255), x_pos, y_pos);
		else if (str[i] == '0')
			fill_tile(data->map_img, get_rgba(255, 255, 255, 255), x_pos,
				y_pos);
		else if (str[i] == 'W' || str[i] == 'N' || str[i] == 'E'
			|| str[i] == 'S')
			fill_tile(data->map_img, get_rgba(255, 255, 255, 255), x_pos,
				y_pos);
		x_pos += TILE_SIZE;
		i++;
	}
}

void	spawn_player(t_data *data)
{
	draw_point(data, (int)data->p_x, (int)data->p_y, get_rgba(0, 255, 0, 255));
	// mlx_put_pixel(data->img, data->p_x, data->p_y, get_rgba(0, 255, 0, 255));
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

int	initial_tile(t_data *data, double p_x1, double p_y1)
{
	int	i;
	int	j;
	int	new_i;
	int	new_j;

	i = data->p_y / TILE_SIZE;
	j = data->p_x / TILE_SIZE;
	new_i = data->p_y / TILE_SIZE;
	new_j = data->p_x / TILE_SIZE;
	if (i == new_i && j == new_j)
		return (1);
	return (0);
}

void	print_dirs(t_data *data)
{
	if (data->ray_h_dire == LEFT)
		printf("Ray Left\n");
	else
		printf("Ray Right\n");
	if (data->ray_v_dire == UP)
		printf("Ray Up\n");
	else
		printf("Ray Down\n");
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
		mlx_put_pixel(data->map_img, (int)(round(p_x)), (int)(round(p_y)),
			get_rgba(255, 0, 0, 255));
		p_x += x_inc;
		p_y += y_inc;
		i++;
	}
	return (0);
}

double	pethago_distance(double x2, double x1, double y2, double y1)
{
	if ((isinf(x1) || isinf(x2) || isinf(y1) || isinf(y2)))
		return (99999999.0);
	return (sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))));
}

void	draw_point(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = -3;
	j = -3;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			mlx_put_pixel(data->map_img, x + i, y + j, color);
			j++;
		}
		mlx_put_pixel(data->map_img, x + i, y + j, color);
		i++;
	}
}

void	update_dire(t_data *data, double deg)
{
	deg = normalized_angle(deg);
	if (deg > 0 && deg < M_PI)
		data->ray_v_dire = UP;
	else
		data->ray_v_dire = DOWN;
	if ((deg < 0.5 * M_PI) || (deg > 1.5 * M_PI))
		data->ray_h_dire = RIGHT;
	else
		data->ray_h_dire = LEFT;
}

double	first_hor_intersection(t_data *data, double deg)
{
	data->first_h_x = 0;
	data->first_h_y = 0;
	if (data->ray_v_dire == UP)
		data->first_h_y = floor(data->p_y / TILE_SIZE) * TILE_SIZE - 0.01;
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
		data->first_v_x = floor(data->p_x / TILE_SIZE) * TILE_SIZE - 0.01;
	data->first_v_y = data->p_y + (data->first_v_x - data->p_x) * (tan(deg) *
			-1);
	return (0);
}

double	hor_intersections(t_data *data, double deg, int *hit_wall)
{
	data->next_h_x = data->first_h_x;
	data->next_h_y = data->first_h_y;
	data->xa = 0;
	data->ya = 0;
	if (data->ray_v_dire == UP)
		data->ya = TILE_SIZE * -1;
	else if (data->ray_v_dire == DOWN)
		data->ya = TILE_SIZE;
	data->xa = data->ya / (tan(deg) * -1);
	while (data->next_h_x <= WIDTH && data->next_h_x >= 0
		&& data->next_h_y <= HEIGHT && data->next_h_y >= 0)
	{
		if (has_wall(data, data->next_h_x, data->next_h_y) || has_wall(data,
				data->next_h_x + 0.01, data->next_h_y) || has_wall(data,
				data->next_h_x, data->next_h_y + 0.01))
		{
			// draw_point(data, data->next_h_x, data->next_h_y, get_rgba(255, 0,
			// 255,
			//	255));
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
	if (data->ray_h_dire == RIGHT)
		data->xa = TILE_SIZE;
	else
		data->xa = TILE_SIZE * -1;
	data->ya = data->xa * (tan(deg) * -1);
	while (data->next_v_x <= WIDTH && data->next_v_x >= 0
		&& data->next_v_y <= HEIGHT && data->next_v_y >= 0)
	{
		if (has_wall(data, data->next_v_x, data->next_v_y) || has_wall(data,
				data->next_v_x + 0.01, data->next_v_y) || has_wall(data,
				data->next_v_x, data->next_v_y + 0.01))
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

void	set_intersections(t_data *data, double deg)
{
	int		found_hor_wall;
	int		found_ver_wall;
	double	hor_dist;
	double	ver_dist;

	hor_dist = 0;
	ver_dist = 0;
	found_hor_wall = 0;
	found_ver_wall = 0;
	first_hor_intersection(data, deg);
	first_ver_intersection(data, deg);
	hor_intersections(data, deg, &found_hor_wall);
	ver_intersections(data, deg, &found_ver_wall);
	if (found_hor_wall)
	{
		hor_dist = pethago_distance(data->hor_hit_x, data->p_x, data->hor_hit_y,
				data->p_y);
	}
	else
		hor_dist = 9999999.00;
	if (found_ver_wall)
	{
		ver_dist = pethago_distance(data->ver_hit_x, data->p_x, data->ver_hit_y,
				data->p_y);
	}
	else
		ver_dist = 99999999.00;
	if (hor_dist < ver_dist)
	{
		data->p_x1 = data->hor_hit_x;
		data->p_y1 = data->hor_hit_y;
		data->distance = hor_dist;
	}
	else
	{
		data->p_x1 = data->ver_hit_x;
		data->p_y1 = data->ver_hit_y;
		data->distance = ver_dist;
	}
	data->distance *= cos(data->rot_angle - data->ray_angle);
}

void	draw_rectangle(t_data *data, int x, int y, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			mlx_put_pixel(data->view, x + j, y + i, COLOR_3);
			j++;
		}
		i++;
	}
}

void	draw_vertical_line(t_data *data, int x, int y_start, int y_end)
{
	int	y;

	// Check if data or data->view is NULL
	if (!data || !data->view)
		return ;
	// Clamp y_start and y_end within valid screen coordinates
	if (y_start < 0)
		y_start = 0;
	if (y_end >= HEIGHT)
		y_end = HEIGHT - 1;
	y = y_start;
	while (y <= y_end)
	{
		if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
			break ;
		mlx_put_pixel(data->view, x, y, HOR_COLOR);
		y++;
	}
}

void	render_wall(t_data *data, int column, double fov)
{
	double	d;
	double	line_height;
	double	wall_height;
	double	projection_plane_distance;

	double y_begin, y_end;
	projection_plane_distance = WIDTH / (2 * tan(fov / 2));
	d = (projection_plane_distance / 2) / tan(fov / 2);
	wall_height = (10 / data->distance) * projection_plane_distance;
	y_begin = (HEIGHT / 2) - (wall_height / 2);
	y_end = (HEIGHT / 2) + (wall_height / 2);
	draw_vertical_line(data, column, (int)y_begin, (int)y_end);
}

void	cast_rays(t_data *data)
{
	double	angle_increment;
	double	distance;
	int		column;
	double	fov;
	double	first_inter_dis;
	double	half_fov;
	double	angle_offset;

	fov = data->p_radius * (M_PI / 180);
	half_fov = fov / 2;
	angle_offset = fov / (NOR - 1);
	angle_increment = fov / NOR;
	data->ray_angle = data->rot_angle - (fov / 2);
	column = 0;
	while (column < NOR)
	{
		data->ray_angle = normalized_angle(data->rot_angle - half_fov + (column
					* angle_offset));
		update_dire(data, data->ray_angle);
		set_intersections(data, data->ray_angle);
		render_wall(data, column, fov);
		cast_ray(data, data->ray_angle);
		data->ray_angle += angle_increment;
		column++;
	}
}

void	put_background(t_data *data)
{
	int	x;
	int	y;
	int	first_half;

	x = 0;
	y = 0;
	first_half = HEIGHT / 2;
	while (x < WIDTH)
	{
		y = 0;
		while (y < first_half)
		{
			mlx_put_pixel(data->view, x, y, COLOR_4);
			y++;
		}
		while (y < HEIGHT)
		{
			mlx_put_pixel(data->view, x, y, COLOR_2);
			y++;
		}
		x++;
	}
}

void	draw_map(t_data *data)
{
	int		x;
	int		y_pos;
	int		i;
	char	**map;

	i = 0;
	x = 0;
	y_pos = 0;
	map = data->map;
	if (data->map_img)
		mlx_delete_image(data->mlx_ptr, data->map_img);
	if (data->view)
		mlx_delete_image(data->mlx_ptr, data->view);
	data->map_img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->view = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	put_background(data);
	map_render(data);
	spawn_player(data);
	cast_rays(data);
	// end_point(data);
	mlx_image_to_window(data->mlx_ptr, data->view, 0, 0);
	mlx_image_to_window(data->mlx_ptr, data->map_img, 0, 0);
}

/*	while (data->next_h_x <= WIDTH && data->next_h_x >= 0
		&& data->next_h_y <= HEIGHT && data->next_h_y >= 0)
	{
		if (has_wall(data, data->next_h_x, data->next_h_y))
		{
			found_hor_wall = 1;
			data->hor_hit_x = data->next_h_x;
			data->hor_hit_y = data->next_h_y;
			break ;
		}
		else
		{
			data->next_h_x += data->xa_v;
			data->next_h_y += data->ya_v;
		}
	}*/