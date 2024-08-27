/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:14:26 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/27 11:17:54 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	in_space(t_data *data)
{
	char	**map;
	int		i;
	int		j;

	map = data->map;
	i = data->p_y / TILE_SIZE;
	j = data->p_x / TILE_SIZE;
	if (map[i][j] == '1')
		return (0);
	return (1);
}

void	keyhooks(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->p_x < WIDTH && data->p_y < HEIGHT)
	{
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
				data->p_y -= 1;
				if (!in_space(data))
					data->p_y += 1;
			}
			if (keydata.key == MLX_KEY_S && (keydata.action == MLX_PRESS
					|| keydata.action == MLX_REPEAT))
			{
				data->p_y += 1;
				if (!in_space(data))
					data->p_y -= 1;
			}
			if (keydata.key == MLX_KEY_D && (keydata.action == MLX_PRESS
					|| keydata.action == MLX_REPEAT))
			{
				data->p_x += 1;
				if (!in_space(data))
					data->p_x -= 1;
			}
			if (keydata.key == MLX_KEY_A && (keydata.action == MLX_PRESS
					|| keydata.action == MLX_REPEAT))
			{
				data->p_x -= 1;
				if (!in_space(data))
					data->p_x += 1;
			}
		}
	}
	draw_map(data);
}
