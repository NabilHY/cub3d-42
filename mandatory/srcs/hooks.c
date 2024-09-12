/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:14:26 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/12 21:13:11 by nhayoun          ###   ########.fr       */
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

void	normalize_angle(t_data *data)
{
	double	TWO_PI;

	TWO_PI = 2.0 * M_PI;
	data->rot_angle = fmod(data->rot_angle, TWO_PI);
	if (data->rot_angle <= 0)
		data->rot_angle += TWO_PI;
}

double	normalized_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	// printf("normalized angle %f == %f deg\n", angle, angle * 180 / M_PI);
	return (angle);
}

int	point_is_wall(t_data *data, double p_x, double p_y)
{
	char	**map;
	int		i;
	int		j;

	map = data->map;
	j = (p_x / TILE_SIZE);
	i = (p_y / TILE_SIZE);
	if (map[i][j] == '1')
		return (1);
	return (0);
}

int	in_space(t_data *data)
{
	char	**map;
	int		ittr;
	int		i;
	int		j;

	map = data->map;
	ittr = -2;
	while (ittr < 3)
	{
		if (point_is_wall(data, data->p_x + ittr, data->p_y))
			return (0);
		ittr++;
	}
	ittr = -2;
	while (ittr < 3)
	{
		i = data->p_x / TILE_SIZE;
		j = data->p_y + ittr / TILE_SIZE;
		if (point_is_wall(data, data->p_x, data->p_y + ittr))
			return (0);
		ittr++;
	}
	return (1);
}

int	ray_in_corner(t_data *data, double p_x, double p_y)
{
	char	**map;
	int		i;
	int		j;

	map = data->map;
	i = (p_y / TILE_SIZE);
	j = (p_x / TILE_SIZE);
	if ((map[i][j] == '1' || map[i][j - 1] == '1') && (map[i + 1][j] == '1'
			|| map[i + 1][j - 1] == '1'))
		return (0);
	return (1);
}

void	keyhooks(mlx_key_data_t keydata, void *param)
{
	t_data	*data;
	double	new_x;
	double	new_y;

	data = (t_data *)param;
	if (data->p_x < WIDTH && data->p_y < HEIGHT)
	{
		if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT
				|| keydata.action == MLX_PRESS))
		{
			data->rot_angle -= data->rot_speed;
			normalize_angle(data);
		}
		if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT
				|| keydata.action == MLX_PRESS))
		{
			data->rot_angle += data->rot_speed;
			normalize_angle(data);
		}
		if (in_space(data))
		{
			if (keydata.key == MLX_KEY_W && (keydata.action == MLX_PRESS
					|| keydata.action == MLX_REPEAT))
			{
				data->p_y -= sin(data->rot_angle) * data->move_speed;
				data->p_x += cos(data->rot_angle) * data->move_speed;
				if (!in_space(data))
				{
					data->p_y += sin(data->rot_angle) * data->move_speed;
					data->p_x -= cos(data->rot_angle) * data->move_speed;
				}
			}
			if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
					|| keydata.action == MLX_REPEAT))
			{
				data->p_y += sin(data->rot_angle) * data->move_speed;
				data->p_x -= cos(data->rot_angle) * data->move_speed;
				if (!in_space(data))
				{
					data->p_y -= sin(data->rot_angle) * data->move_speed;
					data->p_x += cos(data->rot_angle) * data->move_speed;
				}
			}
			if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
					|| keydata.action == MLX_REPEAT))
			{
				data->p_y -= cos(data->rot_angle) * data->move_speed;
				data->p_x -= sin(data->rot_angle) * data->move_speed;
				if (!in_space(data))
				{
					data->p_y += cos(data->rot_angle) * data->move_speed;
					data->p_x += sin(data->rot_angle) * data->move_speed;
				}
			}
			if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
					|| keydata.action == MLX_REPEAT))
			{
				data->p_y += cos(data->rot_angle) * data->move_speed;
				data->p_x += sin(data->rot_angle) * data->move_speed;
				if (!in_space(data))
				{
					data->p_y -= cos(data->rot_angle) * data->move_speed;
					data->p_x -= sin(data->rot_angle) * data->move_speed;
				}
			}
		}
		// printf("%f %f %f direction: %d/%d\n", data->p_x, data->p_y,
		//(data->rot_angle * 180
		//		/ M_PI), data->v_dire, data->h_dire);
		set_direction(data);
		draw_map(data);
		// printf("deg : %f\n", data->rot_angle);
	}
}
