/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:31:29 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/23 19:37:18 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	int			index;
	t_colors	colors;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	index = (y * texture->width + x) * 4;
	colors.r = texture->pixels[index + 1];
	colors.g = texture->pixels[index + 2];
	colors.b = texture->pixels[index + 3];
	colors.a = texture->pixels[index];
	colors.color = (colors.a << 24) | (colors.r << 16)
		| (colors.g << 8) | colors.b;
	return (colors.color);
}
