/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:22:46 by nhayoun           #+#    #+#             */
/*   Updated: 2024/09/22 18:55:33 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(void)
{
	t_data data;

	mock_data(&data);
	data.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", 1);
	mlx_key_hook(data.mlx_ptr, keyhooks, (void *)&data);
	mlx_cursor_hook(data.mlx_ptr, mouse_hook, (void *)&data);
	render_method(&data);
	mlx_loop(data.mlx_ptr);
	mlx_terminate(data.mlx_ptr);
	return (0);
}