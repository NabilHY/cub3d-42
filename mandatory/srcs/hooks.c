/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 16:14:26 by nhayoun           #+#    #+#             */
/*   Updated: 2024/08/25 16:43:44 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"



void	keyhooks(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (data->p_x < WIDTH && data->p_y < HEIGHT)
	{

	}
	draw_map(data);
}
