/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pretests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:09:58 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/29 17:47:36 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ext_test(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	i--;
	if (filename[i] == 'b')
	{
		i--;
		if (filename[i] == 'u')
		{
			i--;
			if (filename[i] == 'c')
			{
				i--;
				if (filename[i] == '.')
					return (1);
			}
		}
	}
	return (0);
}

int	ext_test2(char *filename)
{
	int	i;

	i = 0;
	while (filename[i])
		i++;
	i--;
	if (filename[i] == 'g')
	{
		i--;
		if (filename[i] == 'n')
		{
			i--;
			if (filename[i] == 'p')
			{
				i--;
				if (filename[i] == '.')
					return (1);
			}
		}
	}
	return (0);
}

int	file_existance(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (1);
	else
	{
		close(fd);
		return (0);
	}
}

int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nCouldnt open file\n");
		exit(1);
	}
	return (fd);
}

int	copy_file(char *filename, t_data *data, int i, int j)
{
	int		fd;
	char	*line;

	fd = open_file(filename);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
		i++;
	}
	(free(line), close(fd));
	fd = open_file(filename);
	data->file = malloc(sizeof(char *) * (i + 1));
	if (!data->file)
		return (printf("Error\nFailed Malloc"), exit(1), 1);
	while (j < i)
	{
		data->file[j] = get_next_line(fd);
		j++;
	}
	data->file[j] = NULL;
	return (0);
}
