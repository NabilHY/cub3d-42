/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing_tests2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhayoun <nhayoun@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:46:40 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/23 19:37:18 by nhayoun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	something(t_data *data, int *i, int j) {
  while (data->file[(*i)]) {
    j = 0;
    while (data->file[(*i)][j]) {
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

int	copy_map(t_data *data, int i, int j) {
  int l;
  int max;

  something(data, &i, j);
  j = i;
  while (data->file[i])
    i++;
  data->map = malloc(sizeof(char *) * (i - j + 1));
  l = 0;
  while (data->file[j]) {
    data->map[l++] = ft_strdup(data->file[j]);
    j++;
  }
  data->map[l] = NULL;
  max = 0;
  i = -1;
  while (data->map[++i]) {
    if (ft_strlen(data->map[i]) > max)
      max = ft_strlen(data->map[i]);
  }
  return (data->w_map = max, data->h_map = l, 0);
}
