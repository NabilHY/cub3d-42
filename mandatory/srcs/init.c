/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:33:42 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/18 19:15:06 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



/*
*/
int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
void	fill_tile(mlx_image_t *tile, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < TILE_SIZE)
	{
		while (y < TILE_SIZE)
		{
			mlx_put_pixel(tile, x, y, color);
			y++;
		}
		x++;
	}
}

int	init(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	y = 0;

	mlx->mlx_ptr = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	//mlx->wall_tile = mlx_new_image(mlx->mlx_ptr, TILE_SIZE, TILE_SIZE);
	//mlx->free_tile = mlx_new_image(mlx->mlx_ptr, TILE_SIZE, TILE_SIZE);
	//fill_tile(mlx->wall_tile, get_rgba(60, 60, 60, 255));
	//fill_tile(mlx->wall_tile, get_rgba(240, 240, 240, 255));
	//draw_map(mlx);
	mlx_loop(mlx->mlx_ptr);
	mlx_terminate(mlx->mlx_ptr);
	return (EXIT_SUCCESS);
}