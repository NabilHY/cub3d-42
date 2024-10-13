/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:31:29 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/13 13:33:46 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	int			index;
	uint32_t	color;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0); 
	index = (y * texture->width + x) * 4;
	uint8_t r = texture->pixels[index + 1]; 
	uint8_t g = texture->pixels[index + 2]; 
	uint8_t b = texture->pixels[index + 3];
	uint8_t a = texture->pixels[index];
	color = (a << 24) | (r << 16) | (g << 8) | b;
	return (color);
}
