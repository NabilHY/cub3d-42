/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maaz <ael-maaz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:07:16 by ael-maaz          #+#    #+#             */
/*   Updated: 2024/10/27 16:15:13 by ael-maaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ncount(long n)
{
	int	i;

	if (n == 0)
		i = 1;
	else
		i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*allocate(int *n, long *i)
{
	char	*str;

	if ((*n) < 0)
	{
		str = (char *)malloc(((*i) + 2) * sizeof(char));
		(*i)++;
	}
	else
		str = (char *)malloc(((*i) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	return (str);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(char *s, int *error, int i, int sign)
{
	long long			num;

	if (ft_fcmp(s, "-0") == 0 || ft_fcmp(s, "+0") == 0 || ft_fcmp(s, "0") == 0)
		return (0);
	while (s[i] == '0')
		i++;
	if (s[i] == '\0')
		return (0);
	i = 0;
	num = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i++] == '-')
			sign = -1;
	}
	while (s[i] >= '0' && s[i] <= '9')
		num = num * 10 +(s[i++] - 48);
	if (s[i] != '\0' || num == 0 || (num * sign) > 2147483647
		|| (num * sign) < -2147483648)
		*error = 1;
	return (num * sign);
}

char	*ft_itoa(int n)
{
	long	i;
	long	cpy;
	char	*str;

	cpy = n;
	if (n < 0)
		cpy = (long)n * (-1);
	i = ncount(cpy);
	str = allocate(&n, &i);
	if (!str)
		return (NULL);
	if (n < 0)
		str[0] = '-';
	else if (n == 0)
		str[0] = '0';
	str[i] = '\0';
	while (cpy > 0)
	{
		str[i-- - 1] = (cpy % 10) + 48;
		cpy /= 10;
	}
	return (str);
}
