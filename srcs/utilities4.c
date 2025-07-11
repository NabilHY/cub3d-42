/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:08:50 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/11/03 10:02:12 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	o_rgba(int rgba)
{
	int	a;
	int	opposite_r;
	int	opposite_g;
	int	opposite_b;

	a = rgba & 0xFF;
	opposite_r = 255 -  ((rgba >> 24) & 0xFF);
	opposite_g = 255 -  ((rgba >> 16) & 0xFF);
	opposite_b = 255 - ((rgba >> 8) & 0xFF);
	return (opposite_r << 24 | opposite_g << 16 | opposite_b << 8 | a);
}

void	free_all(t_data *data, t_map_data *x)
{
	free_2d(data->map);
	free_2d(data->file);
	free(x->ceil.str);
	free(x->floor.str);
	free(x->so.str);
	free(x->no.str);
	free(x->ea.str);
	free(x->we.str);
}

int	test_comma(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (1);
	return (0);
}
