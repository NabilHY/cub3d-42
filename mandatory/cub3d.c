/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:22:46 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/21 13:14:42 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mock_data(t_data *data)
{
	data->map = malloc(sizeof(char *) * 15);
	data->map[0] = ft_strdup("        1111111111111111111111111");
	data->map[1] = ft_strdup("        1000000000110000000000001");
	data->map[2] = ft_strdup("        1011000001110000000000001");
	data->map[3] = ft_strdup("        1001000000000000000000001");
	data->map[4] = ft_strdup("111111111011000001110000000000001");
	data->map[5] = ft_strdup("100000000011000001110111110111111");
	data->map[6] = ft_strdup("11110111111111011100000010001");
	data->map[7] = ft_strdup("11110111111111011101010010001");
	data->map[8] = ft_strdup("11000000110101011100000010001");
	data->map[9] = ft_strdup("10000000000000001100000010001");
	data->map[10] = ft_strdup("10000000000000001101010010001");
	data->map[11] = ft_strdup("11000001110101011111011110N0111");
	data->map[12] = ft_strdup("11110111 1110101 101111010001");
	data->map[13] = ft_strdup("11111111 1111111 111111111111");
	data->map[14] = NULL;
}

int	main(void)
{
	t_data data;

	mock_data(&data);
	data.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", 1);
	draw_map(&data);
	mlx_loop(data.mlx_ptr);
	mlx_terminate(data.mlx_ptr);
	// init_data(&data);
	// init(&data);
	return (0);
}