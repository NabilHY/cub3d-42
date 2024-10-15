/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_tests.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:43:30 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/15 19:39:17 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	part_one(char **copy, int *error, int j, int i)
{
	if (copy[i - 1][j] == '0')
		return (*error = 1, 1);
	else if (copy[i + 1][j] == '0')
		return (*error = 1, 1);
	if (j == 0)
	{
		if (copy[i][j + 1] == '0')
			return (*error = 1, 1);
	}
	else if (j == ft_strlen(copy[i]))
	{
		if (copy[i][j - 1] == '0')
			return (*error = 1, 1);
	}
	else
	{
		if (copy[i][j + 1] == '0')
			return (*error = 1, 1);
		else if (copy[i][j - 1] == '0')
			return (*error = 1, 1);
	}
	return (0);
}

int	part_two(char **copy, int *error, int j, int i)
{
	if (copy[i + 1][j] == '0')
		return (*error = 1, 1);
	if (j == 0)
	{
		if (copy[i][j + 1] == '0')
			return (*error = 1, 1);
	}
	else if (j == ft_strlen(copy[i]))
	{
		if (copy[i][j - 1] == '0')
			return (*error = 1, 1);
	}
	else
	{
		if (copy[i][j + 1] == '0')
			return (*error = 1, 1);
		else if (copy[i][j - 1] == '0')
			return (*error = 1, 1);
	}
	return (0);
}

int	part_three(char **copy, int *error, int j, int i)
{
	if (copy[i - 1][j] == '0')
		return (*error = 1, 1);
	if (j == 0)
	{
		if (copy[i][j + 1] == '0')
			return (*error = 1, 1);
	}
	else if (j == ft_strlen(copy[i]))
	{
		if (copy[i][j - 1] == '0')
			return (*error = 1, 1);
	}
	else
	{
		if (copy[i][j + 1] == '0')
			return (*error = 1, 1);
		else if (copy[i][j - 1] == '0')
			return (*error = 1, 1);
	}
	return (0);
}

int	another_another_function(char **copy, int *error, int height, int i)
{
	int	j;

	j = -1;
	while (copy[i][++j])
	{
		if (copy[i][j] == ' ')
		{
			if (i > 0 && i < height - 1)
			{
				if (part_one(copy, error, j, i) == 1)
					return (1);
			}
			else if (i == 0)
			{
				if (part_two(copy, error, j, i) == 1)
					return (1);
			}
			else
			{
				if (part_three(copy, error, j, i) == 1)
					return (1);
			}
		}
	}
	return (0);
}

int	another_function(char **copy, int *error, int height, int i)
{
	while (copy[++i])
	{
		if (another_another_function(copy, error, height, i) == 1)
			return (*error = 1, 1);
	}
	return (0);
}
