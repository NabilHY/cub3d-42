/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 19:31:29 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/11 09:56:05 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

uint32_t	get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	int			index;
	uint32_t	color;

	// Ensure x and y are within bounds
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0); // Return 0 for invalid coordinates
	// Calculate the pixel's index in the pixel buffer
	index = (y * texture->width + x) * 4;
	// Extract RGBA components from the pixel buffer
	uint8_t r = texture->pixels[index + 1]; // Red
	uint8_t g = texture->pixels[index + 2]; // Green
	uint8_t b = texture->pixels[index + 3]; // Blue
	uint8_t a = texture->pixels[index];     // Alpha
	// Combine the color components into a 32-bit color value (0xAARRGGBB)
	color = (a << 24) | (r << 16) | (g << 8) | b;
	return (color);
}

void	test_function(mlx_t *mlx)
{
	mlx_texture_t	*texture;
	mlx_image_t		*img;
	uint32_t		i;
	uint32_t		j;

	texture = mlx_load_png("./textures/wall1.png");
	img = mlx_new_image(mlx, texture->width, texture->height);
	printf("%u\n", texture->height);
	i = 0;
	while (i < texture->width)
	{
		j = 0;
		while (j < texture->height)
		{
			mlx_put_pixel(img, i, j, get_pixel_color(texture, i, j));
			j++;
		}
		i++;
	}
	(void)img;
	(void)texture;
}
