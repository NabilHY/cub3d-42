/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_tests2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:46:40 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/29 17:38:28 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	something(t_data *data, int *i, int j)
{
	while (data->file[(*i)])
	{
		j = 0;
		while (data->file[(*i)][j])
		{
			if (data->file[(*i)][j] == ' ')
				j++;
			else
				break ;
		}
		if (data->file[(*i)][j] == '\0')
			(*i)++;
		else
			break ;
	}
}

int	copy_map(t_data *data, int i, int j)
{
	int	l;
	int	max;

	something(data, &i, j);
	j = i;
	while (data->file[i])
		i++;
	data->map = malloc(sizeof(char *) * (i - j + 1));
	l = 0;
	while (data->file[j])
	{
		data->map[l++] = ft_strdup(data->file[j]);
		j++;
	}
	data->map[l] = NULL;
	max = 0;
	i = -1;
	while (data->map[++i])
	{
		if (ft_strlen(data->map[i]) > max)
			max = ft_strlen(data->map[i]);
	}
	return (data->w_map = max, data->h_map = l, 0);
}

void	clone_map(t_data *data, int i)
{
	int	k;

	k = 0;
	while (++i < data->h_map)
	{
		k = 0;
		data->copy[i] = malloc(data->w_map + 1);
		ft_memset(data->copy[i], ' ', data->w_map);
		data->copy[i][data->w_map] = '\0';
		while (data->map[i][k])
		{
			data->copy[i][k] = data->map[i][k];
			k++;
		}
	}
	data->copy[i] = NULL;
}
