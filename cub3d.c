/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:22:46 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/29 18:47:28 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_map_data(t_map_data *x)
{
	x->ceil.count = 0;
	x->floor.count = 0;
	x->ceil.str = NULL;
	x->ea.str = NULL;
	x->floor.str = NULL;
	x->no.str = NULL;
	x->we.str = NULL;
	x->so.str = NULL;
	x->ea.count = 0;
	x->no.count = 0;
	x->we.count = 0;
	x->so.count = 0;
}

void	free_textures(t_data *data)
{
	if (data->texture_ea)
		mlx_delete_texture(data->texture_ea);
	if (data->texture_we)
		mlx_delete_texture(data->texture_we);
	if (data->texture_so)
		mlx_delete_texture(data->texture_so);
	if (data->texture_no)
		mlx_delete_texture(data->texture_no);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_map_data	x;

	init_map_data(&x);
	if (ac == 2)
	{
		if (test_map_validity(av[1], &data, &x) == 1)
			return (1);
		init_data(&data, x);
		if (test_texture_opening(&data) == 1)
			return (free_all(&data, &x), free_textures(&data), 1);
		data.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", 1);
		mlx_key_hook(data.mlx_ptr, keyhooks, (void *)&data);
		mlx_cursor_hook(data.mlx_ptr, mouse_hook, (void *)&data);
		render_method(&data);
		mlx_loop(data.mlx_ptr);
		mlx_terminate(data.mlx_ptr);
		return (0);
	}
	printf("Error\nWrong arguments\n");
}
