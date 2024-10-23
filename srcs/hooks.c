/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:14:26 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/23 19:37:18 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_rotation(mlx_key_data_t keydata, t_data *data) {
  if (keydata.key == MLX_KEY_RIGHT &&
      (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
    data->rot_angle -= data->rot_speed;
  if (keydata.key == MLX_KEY_LEFT &&
      (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
    data->rot_angle += data->rot_speed;
  normalize_angle(data);
}

void	mouse_hook(double xdelta, double ydelta, void *param) {
  t_data *data;
  double delta_x;

  data = (t_data *)param;
  delta_x = xdelta - data->last_x;
  if (xdelta > 0 && xdelta <= WIDTH && ydelta > 0 && ydelta <= HEIGHT) {
    data->rot_angle -= delta_x * 0.01;
    data->rot_angle = normalized_angle(data->rot_angle);
    data->last_x = xdelta;
    data->prev_rot = data->rot_angle;
    render_method(data);
  } else {
    mlx_set_mouse_pos(data->mlx_ptr, WIDTH / 2, HEIGHT / 2);
    data->rot_angle = data->prev_rot;
    data->last_x = WIDTH / 2;
  }
}

void	keyhooks(mlx_key_data_t keydata, void *param) {
  t_data *data;

  data = (t_data *)param;
  if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS) {
    mlx_terminate(data->mlx_ptr);
    exit(0);
  }
  if (data->p_x < data->w_map && data->p_y < data->h_map) {
    player_rotation(keydata, data);
    player_mouvements(keydata, data);
    set_direction(data);
    render_method(data);
  }
}
