/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:14:26 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/02 20:46:27 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//
//
//
//

int	in_space(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	map = data->map;
	i = data->p_x / TILE_SIZE;
	j = data->p_y / TILE_SIZE;
	if (map[j][i] == '1')
		return (0);
	return (1);
}

int	ray_in_space(t_data *data, double p_x, double p_y)
{
	char	**map;
	int		i;
	int		j;

	map = data->map;
	// printf("p_x::: %f  p_y::: %f\n", p_x, p_y);
	j = (p_x / TILE_SIZE);
	i = (p_y / TILE_SIZE);
	// printf("i::: %d j::: %d\n", i, j);
	if (map[i][j] == '1')
		return (0);
	return (1);
}

int	ray_in_corner(t_data *data, double p_x, double p_y)
{
	char	**map;
	int		i;
	int		j;

	map = data->map;
	j = (p_x / TILE_SIZE);
	i = (p_y / TILE_SIZE);
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
		printf("%f %f %f \n", sin(data->rot_angle), cos(data->rot_angle), (180
				/ M_PI) * data->rot_angle);
		if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT
				|| keydata.action == MLX_PRESS))
			data->rot_angle += data->rot_speed;
		if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT
				|| keydata.action == MLX_PRESS))
			data->rot_angle -= data->rot_speed;
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
		}
		draw_map(data);
	}
}
