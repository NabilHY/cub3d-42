/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures_tests2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:45:33 by ael-maaz          #+#    #+#             */
<<<<<<< HEAD:mandatory/srcs/map_textures_tests2.c
/*   Updated: 2024/10/17 22:00:09 by ael-maaz         ###   ########.fr       */
=======
/*   Updated: 2024/10/23 19:37:18 by nhayoun          ###   ########.fr       */
>>>>>>> 55d2993d514c6f0538da5674bfe47966062bd30c:srcs/map_textures_tests2.c
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	test_numbers(char **args, int *error, char *flag, t_map_data *x)
{
	int	i;
	int	num;

	i = 0;
	while (args[i])
	{
		num = ft_atoi(args[i], error, 0, 1);
		if (*error != 0 || num < 0 || num > 255)
			return (free_2d(args), 1);
		if (ft_fcmp(flag, "F") == 0)
			x->fcolor[i] = num;
		else if (ft_fcmp(flag, "C") == 0)
			x->ccolor[i] = num;
		i++;
	}
	free_2d(args);
	return (0);
}

int	test_colors(char **line, char *flag, t_map_data *x, int i)
{
	char	**args;
	int		error;

	error = 0;
	if (ft_fcmp(flag, "F") == 0 || ft_fcmp(flag, "C") == 0)
	{
		if (test_comma(line[1]) == 1)
			return (1);
		args = ft_split(line[1], ',');
		while (args[i])
			i++;
		if (i == 3)
		{
			if (test_numbers(args, &error, flag, x) == 1)
				return (1);
		}
		else
			return (printf("invalid argument for F/C\n"), free_2d(args), 1);
	}
	return (0);
}

int	open_textures(char **line, char *flag, t_map_data *x)
{
	int	fd;

	(void)x;
	if (ft_fcmp(flag, "NO") == 0 || ft_fcmp(flag, "SO") == 0 || ft_fcmp(flag,
			"WE") == 0 || ft_fcmp(flag, "EA") == 0)
	{
		fd = open(line[1], O_RDONLY);
		if (fd == -1)
		{
			printf("invalid texture file\n");
			return (1);
		}
		else if (ext_test2(line[1]) == 0)
			return (printf("invalid extension for texture file\n"), 1);
	}
	return (0);
}
