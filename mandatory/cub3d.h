/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:23:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/15 18:16:05 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800
# define TILE_SIZE 30

typedef struct s_data
{
	char		**map;
	int			p_x;
	int			p_y;
	int			w_map;
	int			h_map;
}				t_data;

typedef struct s_mlx
{
	mlx_image_t	*free_tile;
	mlx_image_t	*wall_tile;
	mlx_image_t	*img;
	mlx_t		*mlx_ptr;
	t_data		*data;
}				t_mlx;

int				init(t_mlx *mlx);
void			draw_map(t_mlx *mlx);

#endif