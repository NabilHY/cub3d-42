/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 18:25:06 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/12 18:10:36 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, int n)
{
	int	i;

	if (n == 0)
		return ;
	i = 0;
	while (i < n)
	{
		*(unsigned char *)(s + i) = 0;
		i++;
	}
}

void	*ft_memcpy(void *dst, const void *src, int n)
{
	int	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		*(unsigned char *)(dst + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, int len)
{
	if (!dst && !src)
		return (NULL);
	if (dst < src)
		ft_memcpy(dst, src, len);
	else
	{
		while (len)
		{
			len--;
			*(unsigned char *)(len + dst) = *(unsigned char *)(len + src);
		}
	}
	return (dst);
}

char	*ft_strdup(const char *s1)
{
	char	*buffer;
	int		len;

	len = ft_strlen(s1);
	buffer = (char *)malloc((len + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (len == 0)
	{
		ft_bzero(buffer, 1);
		return (buffer);
	}
	ft_memmove(buffer, s1, len + 1);
	return (buffer);
}
