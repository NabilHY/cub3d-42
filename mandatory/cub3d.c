/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:22:46 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/15 15:59:49 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_data data;

	mock_data(&data);
	data.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", 0);
	mlx_key_hook(data.mlx_ptr, keyhooks, (void *)&data);
	render_method(&data);
	//mlx_cursor_hook(data.mlx_ptr, mouse_hook, (void *)&data);
	mlx_loop(data.mlx_ptr);
	mlx_terminate(data.mlx_ptr);
	return (0);
}