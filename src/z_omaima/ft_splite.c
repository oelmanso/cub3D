/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 10:59:35 by oelmanso          #+#    #+#             */
/*   Updated: 2025/12/28 10:59:56 by oelmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*ss;
	int		i;
	int		siz;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
		siz = ft_strlen(s) - start;
	else
		siz = len;
	ss = malloc((siz + 1) * sizeof(char));
	if (!ss)
		return (NULL);
	gc_add_node_back(gc_instance(), gc_new_node(ss));
	i = 0;
	while (i < siz)
	{
		ss[i] = s[start + i];
		i++;
	}
	ss[i] = '\0';
	return (ss);
}

static int	ft_nworth(char *s, char c)
{
	int	count;

	count = 1;
	if (!s || !*s)
		return (1);
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count + 1);
}

static char	**ft_fill(char *s, char c, char **arr)
{
	int	start;
	int	i;
	int	j;

	start = 0;
	i = 0;
	j = 0;
	while (1)
	{
		if (s[i] == c || s[i] == '\0')
		{
			arr[j] = ft_substr(s, start, i - start);
			if (!arr[j])
				return (NULL);
			j++;
			if (s[i] == '\0')
				break ;
			start = i + 1;
		}
		i++;
	}
	arr[j] = NULL;
	return (arr);
}

char	**ft_split(char *s, char c)
{
	char	**a;

	if (!s)
		return (NULL);
	a = malloc(ft_nworth(s, c) * sizeof(char *));
	if (!a)
		return (NULL);
	gc_add_node_back(gc_instance(), gc_new_node(a));
	return (ft_fill(s, c, a));
}
