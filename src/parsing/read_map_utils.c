/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 11:05:30 by oelmanso          #+#    #+#             */
/*   Updated: 2025/12/28 11:06:15 by oelmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	print_error1(char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s1;
	size_t			i;

	s1 = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		s1[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	s = malloc(count * size);
	if (!s)
		return (NULL);
	gc_add_node_back(gc_instance(), gc_new_node(s));
	ft_bzero(s, (count * size));
	return (s);
}

static int	checker(char s, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		len;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	len = ft_strlen(s1) - 1;
	while (checker(s1[start], set))
		start++;
	if (start == len + 1)
		return (ft_strdup(""));
	while (checker(s1[len], set) && len > start)
		len--;
	ptr = ft_substr(s1, start, (len + 1) - start);
	return (ptr);
}
