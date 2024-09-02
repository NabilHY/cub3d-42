/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:22:46 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/02 20:49:45 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	player_position(t_data *data)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = data->map;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j])
			{
				if (map[i][j] == 'N' || map[i][j] == 'W' || map[i][j] == 'S'
					|| map[i][j] == 'E')
				{
					data->p_x = j * TILE_SIZE;
					data->p_y = i * TILE_SIZE;
					data->p_direction = map[i][j];
				}
			}
			j++;
		}
		i++;
	}
	data->p_x += TILE_SIZE / 2;
	data->p_y += TILE_SIZE / 2;
}

void	mock_data(t_data *data)
{
	data->map = malloc(sizeof(char *) * 15);
	data->map[0] = ft_strdup("        1111111111111111111111111");
	data->map[1] = ft_strdup("        1000000000110001000000001");
	data->map[2] = ft_strdup("        101100000111001W100000001");
	data->map[3] = ft_strdup("        1001000000000001000000001");
	data->map[4] = ft_strdup("111111111011000001110000000000001");
	data->map[5] = ft_strdup("100000000011000001110111110111111");
	data->map[6] = ft_strdup("11110111111111011100000010001");
	data->map[7] = ft_strdup("11110111111111011101010010001");
	data->map[8] = ft_strdup("11000000110101011100000010001");
	data->map[9] = ft_strdup("10000000000000001100000010001");
	data->map[10] = ft_strdup("10000000000000001101010010001");
	data->map[11] = ft_strdup("1100000111010101111101111000111");
	data->map[12] = ft_strdup("11110111 1110101 101111010001");
	data->map[13] = ft_strdup("11111111 1111111 111111111111");
	data->map[14] = NULL;
	player_position(data);
	if (data->p_direction == 'W')
		data->rot_angle = M_PI;
	if (data->p_direction == 'S')
		data->rot_angle = M_PI / 2 + M_PI;
	if (data->p_direction == 'E')
		data->rot_angle = 0;
	if (data->p_direction == 'N')
		data->rot_angle = M_PI / 2;
	data->h_map = 14;
	data->w_map = 33;
	data->p_radius = 60;
	// data->turn_dire = 0;
	data->move_speed = 10;
	data->rot_speed = 50 * (M_PI / 180);
	printf("Player is at position x: %f y: %f with %c direction ,,,, fkn shit: %f \n", data->p_x,
		data->p_y, data->p_direction, data->rot_angle);
}

int	main(void)
{
	t_data data;

	mock_data(&data);
	data.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", 1);
	draw_map(&data);
	mlx_key_hook(data.mlx_ptr, keyhooks, (void *)&data);
	mlx_loop(data.mlx_ptr);
	mlx_terminate(data.mlx_ptr);
	// init_data(&data);
	// init(&data);
	return (0);
}