/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:23:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/26 16:20:50 by nhayoun          ###   ########.fr       */
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
	double		p_x1;
	double		p_y1;
	double		p_radius;
	double		turn_dire;
	double		walk_dire;
	double		rot_angle;
	double		move_speed;
	double		rot_speed;
	char		p_direction;
	int			w_map;
	int			h_map;
}				t_data;

void			draw_map(t_data *data);
void			map_render(t_data *data);
void			spawn_player(t_data *data);
double			scaling_value(double ival, double omin, double omax,
					double imax);
void			end_point(t_data *data);
int				get_rgba(int r, int g, int b, int a);

/* Hooks */
void			keyhooks(mlx_key_data_t keydata, void *param);

#endif