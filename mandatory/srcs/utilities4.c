/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:08:50 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/14 22:40:05 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_opposite_rgba(int rgba)
{
	// Extract each color component from the 32-bit integer
	int r = (rgba >> 24) & 0xFF; // Get the red component
	int g = (rgba >> 16) & 0xFF; // Get the green component
	int b = (rgba >> 8) & 0xFF;  // Get the blue component
	int a = rgba & 0xFF;         // Get the alpha component

	// Invert the RGB components
	int opposite_r = 255 - r;
	int opposite_g = 255 - g;
	int opposite_b = 255 - b;

	// Combine the opposite color components back into a 32-bit integer
	return (opposite_r << 24 | opposite_g << 16 | opposite_b << 8 | a);
}

void free_all(t_data *data, t_map_data *x)
{
    free_2d(data->map);
    free_2d(data->file);
    free(x->ceiling.str);
    free(x->floor.str);
    free(x->so.str);
    free(x->no.str);
    free(x->ea.str);
    free(x->we.str);
}

int test_comma(char *str)
{
    int i;
    i = 0;
    int count;
    count = 0;
    while(str[i])
    {
        if(str[i] == ',')
            count++;
        i++;
    }
    if(count != 2)
        return 1;
    return 0;
}