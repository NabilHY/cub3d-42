/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 12:22:46 by nhayoun           #+#    #+#             */
/*   Updated: 2024/10/14 19:32:09 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_map_data(t_map_data *x)
{
	x->ceiling.count = 0;
	x->floor.count = 0;
	x->ceiling.str = NULL;
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

void ll(void)
{
	system("leaks cub3D");
}

int	main(int ac, char **av)
{
	t_data data;
	t_map_data x;
	atexit(ll);
	init_map_data(&x);
	if (ac == 2)
	{
		if (test_map_validity(av[1], &data, &x) == 1)
			return (1);
		init_data(&data, x);
		data.mlx_ptr = mlx_init(WIDTH, HEIGHT, "cub3d", 1);
		mlx_key_hook(data.mlx_ptr, keyhooks, (void *)&data);
		mlx_cursor_hook(data.mlx_ptr, mouse_hook, (void *)&data);
		render_method(&data);
		mlx_loop(data.mlx_ptr);
		mlx_terminate(data.mlx_ptr);
		return (0);
	}
	printf("wrong arguments\n");
}
