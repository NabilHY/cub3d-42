/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:23:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/21 13:22:39 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libr/libr.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 1200
# define HEIGHT 800
# define TILE_SIZE 30

typedef struct s_data
{
	mlx_image_t	*img;
	mlx_t		*mlx_ptr;
	char		**map;
	double		p_x;
	double		p_y;
	char		p_direction;
	int			w_map;
	int			h_map;
}				t_data;

int				init(t_data *data);
void			draw_map(t_data *data);
void			map_render(t_data *data);

#endif