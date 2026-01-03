/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 21:55:26 by zhassna           #+#    #+#             */
/*   Updated: 2026/01/02 21:56:36 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_strlen(char *s1)
{
	int	i;

	i = 0;
	while (s1[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	char	*dup;
	int		len;
	int		i;

	len = ft_strlen(s1);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	gc_add_node_back(gc_instance(), gc_new_node(dup));
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char	*strdup_map(char *s1, int len)
{
	char	*dup;
	int		i;

	dup = ft_calloc((len + 1), sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	return (dup);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int		sign;
	long	nb;

	nb = 0;
	sign = 1;
	while (*str == 32 || (*str <= 13 && *str >= 9))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}
