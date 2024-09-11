/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map12.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:02:58 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/10 15:50:48 by nhayoun          ###   ########.fr       */
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
	if (data->h_dire == LEFT)
		printf("Ray Left\n");
	else
		printf("Ray Right\n");
	if (data->v_dire == UP)
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
		// if (has_wall(data, p_x, p_y))
		//	break ;
		// if (!ray_in_space(data, p_x, p_y))
		//	break ;
		mlx_put_pixel(data->img, (int)(round(p_x)), (int)(round(p_y)),
			get_rgba(255, 0, 0, 255));
		p_x += x_inc;
		p_y += y_inc;
		i++;
	}
	return (0);
}

double	cast_ray2(t_data *data, double ray_deg, double x, double y)
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
	dx = x - data->p_x;
	dy = y - data->p_y;
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	while (i <= step)
	{
		// if (has_wall(data, p_x, p_y))
		//	break ;
		// if (!ray_in_space(data, p_x, p_y))
		//	break ;
		mlx_put_pixel(data->img, (int)(round(p_x)), (int)(round(p_y)),
			get_rgba(0, 255, 0, 255));
		p_x += x_inc;
		p_y += y_inc;
		i++;
	}
	return (0);
}

void	first_interaction(t_data *data, double deg)
{
	double	hor_dist;
	double	ver_dist;
	double	distance;

	hor_dist = 0;
	ver_dist = 0;
	if (data->ray_v_dire == UP)
		data->first_v_y = floor(data->p_y / TILE_SIZE) * TILE_SIZE - 1;
	else if (data->ray_v_dire == DOWN)
		data->first_v_y = floor(data->p_y / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	data->first_v_x = data->p_x + ((data->p_y - data->first_v_y) / tan(deg));
	ver_dist = sqrt((data->first_v_y - data->p_y) * (data->first_v_y
				- data->p_y) + (data->first_v_x - data->p_x) * (data->first_v_x
				- data->p_x));
	//
	if (data->ray_h_dire == RIGHT)
		data->first_h_x = floor(data->p_x / TILE_SIZE) * TILE_SIZE + TILE_SIZE;
	else if (data->ray_h_dire == LEFT)
		data->first_h_x = floor(data->p_x / TILE_SIZE) * TILE_SIZE - 1;
	data->first_h_y = data->p_y + ((data->p_x - data->first_h_x) * tan(deg));
	hor_dist = sqrt((data->first_h_y - data->p_y) * (data->first_h_y
				- data->p_y) + (data->first_h_x - data->p_x) * (data->first_h_x
				- data->p_x));
	data->next_h_x = data->first_h_x;
	data->next_h_y = data->first_h_y;
	data->next_v_x = data->first_v_x;
	data->next_v_y = data->first_v_y;
	if (hor_dist < ver_dist)
	{
		data->p_x1 = data->first_h_x;
		data->p_y1 = data->first_h_y;
		draw_point(data, data->p_x1, data->p_y1, get_rgba(255, 0, 255, 255));
		// return (hor/_dist);
	}
	else
	{
		data->p_x1 = data->first_v_x;
		data->p_y1 = data->first_v_y;
		draw_point(data, data->p_x1, data->p_y1, get_rgba(0, 0, 255, 255));
		// return (ver_dist);
	}
}

double	pethago_distance(double x1, double y1, double x2, double y2)
{
	if ((isinf(x1) || isinf(x1) || isinf(x1) || isinf(x1)))
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
			mlx_put_pixel(data->img, x + i, y + j, color);
			j++;
		}
		mlx_put_pixel(data->img, x + i, y + j, color);
		i++;
	}
}

void	update_dire(t_data *data, double deg)
{
	if (deg > 0 && deg < M_PI)
		data->ray_v_dire = UP;
	else
		data->ray_v_dire = DOWN;
	if ((deg < 0.5 * M_PI) || (deg > 1.5 * M_PI))
		data->ray_h_dire = RIGHT;
	else
		data->ray_h_dire = LEFT;
}

double	vertical_intersations(t_data *data, double deg, int *hit_bool)
{
	// if (deg == 90 || deg == 270)
	//	return (0);
	data->xa_v = 0;
	data->ya_v = 0;
	data->next_v_x = data->first_v_x;
	data->next_v_y = data->first_v_y;
	if (data->ray_h_dire == RIGHT)
		data->xa_v = TILE_SIZE;
	else if (data->ray_h_dire == LEFT)
		data->xa_v = -TILE_SIZE;
	data->ya_v = data->xa_v * tan(deg);
	while (data->next_v_x <= WIDTH && data->next_v_x >= 0
		&& data->next_v_y <= HEIGHT && data->next_v_y >= 0)
	{
		draw_point(data, data->next_v_x, data->next_v_y, get_rgba(0, 0, 255,
				255));
		if (has_wall(data, data->next_v_x, data->next_v_y))
		{
			*hit_bool = 1;
			data->ver_hit_x = data->next_v_x;
			data->ver_hit_y = data->next_v_y;
			break ;
		}
		else
		{
			data->next_v_x += data->xa_v;
			data->next_v_y += data->ya_v;
			// if (isinf(data->next_v_x) || isinf(data->next_v_y)
			//	|| isnan(data->next_v_x) || isnan(data->next_v_y))
			//{
			//	data->ver_distance = 99999999.00;
			//	break ;
			//}
		}
	}
	return (0);
}

double	horizontal_intersations(t_data *data, double deg, int *hit_bool)
{
	// if (deg == 0 || deg == 180)
	//	return (0);
	data->xa_h = 0;
	data->ya_h = 0;
	data->next_h_x = data->first_h_x;
	data->next_h_y = data->first_h_y;
	if (data->ray_v_dire == UP)
		data->ya_h = -TILE_SIZE;
	else if (data->ray_v_dire == DOWN)
		data->ya_h = TILE_SIZE;
	data->xa_h = data->ya_h / tan(deg);
	while (data->next_h_x <= WIDTH && data->next_h_x >= 0
		&& data->next_h_y <= HEIGHT && data->next_h_y >= 0)
	{
		draw_point(data, data->next_h_x, data->next_h_y, get_rgba(255, 0, 255,
				255));
		if (has_wall(data, data->next_h_x, data->next_h_y))
		{
			*hit_bool = 1;
			data->hor_hit_x = data->next_h_x;
			data->hor_hit_y = data->next_h_y;
			break ;
		}
		else
		{
			//!
			data->next_h_x -= data->xa_h;
			data->next_h_y += data->ya_h;
			// if (isinf(data->next_h_x) || isinf(data->next_h_y)
			//	|| isnan(data->next_h_x) || isnan(data->next_h_y))
			//{
			//	data->hor_distance = 99999999.00;
			//	break ;
			//}
		}
	}
	return (0);
}

void	other_interractions(t_data *data, double deg)
{
	double	distance;
	int		found_hor_wall;
	int		found_ver_wall;

	found_hor_wall = 0;
	found_ver_wall = 0;
	horizontal_intersations(data, deg, &found_hor_wall);
	// vertical_intersations(data, deg, &found_ver_wall);
	if (found_hor_wall)
		data->hor_distance = pethago_distance(data->p_x, data->p_y,
				data->hor_hit_x, data->hor_hit_y);
	else
		data->hor_distance = 99999999.00;
	if (found_ver_wall)
		data->ver_distance = pethago_distance(data->p_x, data->p_y,
				data->ver_hit_x, data->ver_hit_y);
	else
		data->ver_distance = 99999999.00;
	if (data->hor_distance < data->ver_distance)
	{
		data->p_x1 = data->hor_hit_x;
		data->p_y1 = data->hor_hit_y;
	}
	else
	{
		data->p_x1 = data->ver_hit_x;
		data->p_y1 = data->ver_hit_y;
	}
}

void	cast_rays(t_data *data)
{
	double	ray_deg;
	double	angle_increment;
	double	distance;
	int		column;
	double	fov;
	double	first_inter_dis;

	fov = data->p_radius * (M_PI / 180);
	angle_increment = fov / NOR;
	// ray_deg = normalized_angle(data->rot_angle - (fov / 2));
	ray_deg = normalized_angle(data->rot_angle);
	column = 0;
	// while (column < NOR)
	//{
	ray_deg = normalized_angle(ray_deg);
	printf("angle :: %f\n", ray_deg * 180 / M_PI);
	update_dire(data, ray_deg);
	first_interaction(data, ray_deg);
	// other_interractions(data, ray_deg);
	// end_point(data, ray_deg);
	print_dirs(data);
	cast_ray(data, ray_deg);
	// printf("ray %d direction %d/%d \n", column, data->h_dire,
	// data->v_dire);
	ray_deg += angle_increment;
	column++;
	//}
}

void	draw_map(t_data *data)
{
	int		x;
	int		y_pos;
	int		i;
	char	**map;

	;
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

double	ver_intersections(t_data *data, double deg, int *hit_wall)
{
	data->next_v_x = data->first_v_x;
	data->next_v_y = data->first_v_y;
	data->xa = 0;
	data->ya = 0;
	if (data->h_dire == RIGHT)
		data->xa = TILE_SIZE;
	else if (data->h_dire == LEFT)
		data->xa = TILE_SIZE * -1;
	data->ya = data->xa * tan(deg);
	while (data->next_v_x <= WIDTH && data->next_v_x >= 0
		&& data->next_v_y <= HEIGHT && data->next_v_y >= 0)
	{
		draw_point(data, data->next_h_x, data->next_h_y, get_rgba(0, 0, 255,
				255));
		if (has_wall(data, data->next_v_x, data->next_v_y))
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