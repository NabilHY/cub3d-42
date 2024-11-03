/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:23:10 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/29 18:57:41 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "./MLX42/include/MLX42/MLX42.h"
# include "./libr/libr.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WIDTH 800
# define NOR 800
# define HEIGHT 600
# define TILE_SIZE 10
# define RES 30
# define LINE_HEIGHT 30

# define LEFT 1
# define RIGHT 2
# define DOWN 3
# define UP 4

typedef struct s_util
{
	char			*str;
	int				count;
}					t_util;
typedef struct s_map_data
{
	t_util			floor;
	t_util			ceil;
	t_util			no;
	t_util			so;
	t_util			ea;
	t_util			we;
	int				fcolor[3];
	int				ccolor[3];
}					t_map_data;

typedef struct s_vline
{
	double			wall_height;
	double			projection_plane_distance;
	int				y_begin;
	int				y_end;
}					t_vline;

typedef struct s_data
{
	mlx_image_t		*minimap;
	mlx_image_t		*view;
	mlx_texture_t	*texture_no;
	mlx_texture_t	*texture_we;
	mlx_texture_t	*texture_so;
	mlx_texture_t	*texture_ea;
	mlx_t			*mlx_ptr;
	double			*dist;
	char			**map;
	char			**copy;
	char			**file;
	double			p_x;
	double			p_y;
	double			p_x1;
	double			p_y1;
	double			first_h_x;
	double			first_h_y;
	double			first_v_x;
	double			first_v_y;
	double			next_h_x;
	double			next_h_y;
	double			next_v_x;
	double			next_v_y;
	double			xa;
	double			ya;
	double			hor_hit_x;
	double			hor_hit_y;
	double			ver_hit_x;
	double			ver_hit_y;
	double			hor_distance;
	double			ver_distance;
	double			p_radius;
	double			rot_angle;
	double			ray_angle;
	double			accum;
	int				ray_v_dire;
	int				ray_h_dire;
	double			move_speed;
	double			rot_speed;
	char			p_direction;
	int				v_dire;
	int				h_dire;
	int				w_map;
	int				h_map;
	int				vertical_inter;
	int				ceiling_color;
	int				floor_color;
	double			prev_rot;
	double			wall_hit_x;
	double			wall_hit_y;
	double			distance;
	double			last_x;
}					t_data;

typedef struct s_points
{
	double			rad;
	double			p_x1;
	double			p_y1;
	double			dx;
	double			dy;
	double			x_inc;
	double			y_inc;
	double			step;
	int				i;
	double			distance;
}					t_points;

typedef struct s_colors
{
	uint32_t		color;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint8_t			a;
}					t_colors;

void				player_mouvements(mlx_key_data_t keydata, t_data *data);
void				render_method(t_data *data);
int					get_rgba(int r, int g, int b, int a);
int					in_space(t_data *data);
void				set_direction(t_data *data);
int					point_is_wall(t_data *data, double x, double y);
void				update_dire(t_data *data, double deg);
void				put_background(t_data *data);
void				cast_rays(t_data *data);
void				draw_vertical_line(t_data *data, int x, t_vline *coors,
						mlx_texture_t *texture);
void				set_intersections(t_data *data, double deg);
double				normalized_angle(double deg);
void				normalize_angle(t_data *data);

int					has_wall(t_data *data, double x, double y);
double				pethago_distance(double x2, double x1, double y2,
						double y1);
void				draw_point(t_data *data, int x, int y, int color);
/* Hooks */
void				keyhooks(mlx_key_data_t keydata, void *param);
void				move_up(mlx_key_data_t keydata, t_data *data);
void				move_up(mlx_key_data_t keydata, t_data *data);
void				move_left(mlx_key_data_t keydata, t_data *data);
void				move_down(mlx_key_data_t keydata, t_data *data);
void				move_right(mlx_key_data_t keydata, t_data *data);
void				init_data(t_data *data, t_map_data x);
void				mouse_hook(double xdelta, double ydelta, void *param);
char				*ft_strdup_split(const char *s1);
char				*ft_substr_split(char *s, int start, int len);
char				*ft_strjoin_split(char *s1, char *s2);
char				*ft_strchr_split(const char *s, int c);
char				*get_next_line(int fd);
int					ncount(long n);
char				*allocate(int *n, long *i);
uint32_t			get_pixel_color(mlx_texture_t *texture, uint32_t x,
						uint32_t y);
int					o_rgba(int rgba);
char				**ft_split(char const *s, char c);
// bunda parsing
int					ext_test(char *filename);
int					ext_test2(char *filename);
int					file_existance(char *filename);
int					test_textures(t_data *data, int *index, t_map_data *x,
						int i);
int					copy_file(char *filename, t_data *data, int i, int j);
int					test_map_validity(char *filename, t_data *data,
						t_map_data *x);
void				free_2d(char **arr);
int					inc(int *n);
int					test_numbers(char **args, int *error, char *flag,
						t_map_data *x);
int					test_colors(char **line, char *flag, t_map_data *x, int i);
int					open_textures(char **line, char *flag, t_map_data *x);
int					another_function(char **copy, int *error, int height,
						int i);
int					copy_map(t_data *data, int i, int j);
void				free_all(t_data *data, t_map_data *x);
int					test_comma(char *str);
int					test_texture_opening(t_data *data);
void				clone_map(t_data *data, int i);
// Intersections
double				first_hor_intersection(t_data *data, double deg);
double				first_ver_intersection(t_data *data, double deg);
void				hor_intersections(t_data *data, double deg, int *hit_wall);
void				ver_intersections(t_data *data, double deg, int *hit_wall);

#endif
