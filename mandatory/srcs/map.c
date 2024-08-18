/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 15:02:58 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/15 17:09:20 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//void	put_line(t_mlx *mlx, int x, int y)
//{
//	//while (x > 0)
//	//{
//	//	mlx_put_pixel(mlx->img, x, y, 55);
//	//	x--;
//	//}
//}

void	draw_map(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH - 1)
	{
		y = HEIGHT - 1;
		x += TILE_SIZE;
		while (y > 0)
		{
			mlx_put_pixel(mlx->img, x, y, 0);
			y--;
		}
	}
}
