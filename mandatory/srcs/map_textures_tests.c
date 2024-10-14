/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_textures_tests.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 15:50:58 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/14 22:21:16 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	test_floor_ceiling(char **line, char *flag, t_map_data *x)
{
	if (ft_fcmp(flag, "F") == 0 && increment_func(&x->floor.count))
		x->floor.str = ft_strdup(line[1]);
	if (ft_fcmp(flag, "C") == 0 && increment_func(&x->ceiling.count))
		x->ceiling.str = ft_strdup(line[1]);
	if (ft_fcmp(flag, "NO") == 0 && increment_func(&x->no.count))
		x->no.str = ft_strdup(line[1]);
	if (ft_fcmp(flag, "SO") == 0 && increment_func(&x->so.count))
		x->so.str = ft_strdup(line[1]);
	if (ft_fcmp(flag, "WE") == 0 && increment_func(&x->we.count))
		x->we.str = ft_strdup(line[1]);
	if (ft_fcmp(flag, "EA") == 0 && increment_func(&x->ea.count))
		x->ea.str = ft_strdup(line[1]);
}

int	test_characters(char **map, t_map_data *x)
{
	int	i;
	int	count;
	int	j;

	(void)x;
	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				count++;
			else if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ')
				return (1);
			j++;
		}
		i++;
	}
	if (count != 1)
		return (1);
	return (0);
}

int	test_line(char **line, t_map_data *x, int *state, int i)
{
	while (line[i])
		i++;
	if (ft_fcmp(line[0], "F") == 0 || ft_fcmp(line[0], "C") == 0
		|| ft_fcmp(line[0], "NO") == 0 || ft_fcmp(line[0], "SO") == 0
		|| ft_fcmp(line[0], "EA") == 0 || ft_fcmp(line[0], "WE") == 0)
	{
		if (i != 2)
			return (*state = 3, printf("wrong parameters\n"), 1);
		else
		{
			test_floor_ceiling(line, line[0], x);
			if (test_colors(line, line[0], x, 0) == 1)
				return (printf("failed test colors\n"), *state = 1, 1);
			if (open_textures(line, line[0], x) == 1)
				return (printf("failed opening textures\n"), *state = 1, 1);
			return (0);
		}
	}
	else
		return (1);
}

int	sub_function(t_data *data, t_map_data *x, int *state)
{
	char	**line;
	int		i;

	i = 0;
	while (data->file[i])
	{
		if (ft_fcmp(data->file[i], "") == 0)
		{
			i++;
			continue ;
		}
		line = ft_split(data->file[i], ' ');
		if (test_line(line, x, state, 0) == 1)
		{
			free_2d(line);
			break ;
		}
		free_2d(line);
		i++;
	}
	return (i);
}

int	test_textures(t_data *data, int *index, t_map_data *x, int i)
{
	int	state;

	state = 0;
	i = sub_function(data, x, &state);
	if (!x->ceiling.str || !x->floor.str || !x->no.str || !x->so.str
		|| !x->we.str || !x->ea.str || state > 0)
		return (printf("bad map\n"), 1);
	if (x->ceiling.count != 1 || x->floor.count != 1 || x->no.count != 1
		|| x->so.count != 1 || x->we.count != 1 || x->ea.count != 1)
		return (printf("duplicate data\n"), 1);
	if (test_characters(data->file + i, x) == 1)
		return (printf("bad map\n"), 1);
	*index = i;
	return (*index = i, 0);
}
