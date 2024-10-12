/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:02:58 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/12 15:14:23 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	if (!(j > 0 && j * TILE_SIZE < data->h_map && i > 0
			&& i < (int)ft_strlen(map[j])) || map[j][i] == '1')
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

int	checker(t_data *data, double p_x, double p_y)
{
	char	**map;
	int		i;
	int		j;

	map = data->map;
	j = (int)(p_x / TILE_SIZE);
	i = (int)(p_y / TILE_SIZE);
	if (i < 0 || j < 0 || i * TILE_SIZE >= data->h_map || j
		* TILE_SIZE >= data->w_map || ft_strlen(map[i]) * TILE_SIZE < j
		* TILE_SIZE)
		return (1);
	if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S'
		|| map[i][j] == 'E')
		return (0);
	if (map[i][j] == '1' || map[i][j] != '0')
		return (1);
	return (0);
}

void	end_point(t_data *data, double x, double y)
{
	t_points	p;

	p.distance = 10;
	p.i = 0;
	p.rad = data->rot_angle;
	p.dx = p.distance * cos(p.rad);
	p.dy = p.distance * (sin(p.rad) * -1);
	p.p_x1 = 50 + p.dx;
	p.p_y1 = 50 + p.dy;
	if (fabs(p.dx) > fabs(p.dy))
		p.step = fabs(p.dx);
	else
		p.step = fabs(p.dy);
	p.x_inc = p.dx / p.step;
	p.y_inc = p.dy / p.step;
	while (p.i <= p.step)
	{
		mlx_put_pixel(data->minimap, (int)(round(x)), (int)(round(y)),
			get_rgba(189, 195, 199, 255));
		x += p.x_inc;
		y += p.y_inc;
		p.i++;
	}
}

void	minimap_render(t_data *data)
{
	int	end_x;
	int	end_y;
	int	x;
	int	y;

	x = 0;
	end_x = data->p_x + 50;
	end_y = data->p_y + 50;
	while ((data->p_x - 50) + x < end_x)
	{
		y = 0;
		while ((data->p_y - 50) + y < end_y)
		{
			if ((data->p_x - 50) + x < 0 || (data->p_y - 50) + y < 0
				|| checker(data, (data->p_x - 50) + x, (data->p_y - 50) + y))
				mlx_put_pixel(data->minimap, x, y, get_opposite_rgba(data->floor_color));
			else if (!checker(data, (data->p_x - 50) + x, (data->p_y - 50) + y))
				mlx_put_pixel(data->minimap, x, y, get_opposite_rgba(data->ceiling_color));
			y++;
		}
		x++;
	}
	draw_point(data, 50, 50, get_rgba(0, 255, 0, 255));
	end_point(data, 50, 50);
}

void	render_method(t_data *data)
{
	if (data->view)
		mlx_delete_image(data->mlx_ptr, data->view);
	if (data->minimap)
		mlx_delete_image(data->mlx_ptr, data->minimap);
	data->view = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->minimap = mlx_new_image(data->mlx_ptr, 500, 500);
	put_background(data);
	cast_rays(data);
	minimap_render(data);
	mlx_image_to_window(data->mlx_ptr, data->view, 0, 0);
	mlx_image_to_window(data->mlx_ptr, data->minimap, 10, 10);
}
