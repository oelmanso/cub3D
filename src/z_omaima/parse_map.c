/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 10:58:24 by oelmanso          #+#    #+#             */
/*   Updated: 2025/12/28 10:58:50 by oelmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub.h"

int	close_up_down(char *map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		if (is_allowed(map[i]))
			return (1);
		i++;
	}
	return (0);
}

int	close_left(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i])
	{
		j = 0;
		if (map[i][0] == '\0')
			return (2);
		if (whitespace(map[i][j]))
		{
			while (whitespace(map[i][j]))
				j++;
			if (map[i][j] == '\0')
				return (2);
		}
		if (is_allowed(map[i][j]))
			return (1);
		i++;
	}
	return (0);
}

int	close_right(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i])
	{
		j = ft_strlen(map[i]) - 1;
		if (whitespace(map[i][j]))
		{
			while (whitespace(map[i][j]) && j > 0)
				j--;
		}
		if (is_allowed(map[i][j]))
			return (1);
		i++;
	}
	return (0);
}

int	valid_way(char **map)
{
	int	i;
	int	j;

	i = 1;
	while (map[i + 1])
	{
		j = 1;
		while (map[i][j + 1])
		{
			if (is_allowed(map[i][j]))
			{
				if (is_invalid(map[i][j - 1]) || is_invalid(map[i][j + 1])
					|| (is_invalid(map[i - 1][j]) || is_invalid(map[i + 1][j])))
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	parse_cub_file(t_game *game)
{
	int	len;
	int	left;

	len = 0;
	if (check_parse_file(game))
		print_error("Invalid file structure");
	full_map(game);
	while (game->map[len])
		len++;
	left = close_left(game->map);
	if (left == 2)
		print_error("Invalid map : empty line");
	if (close_up_down(game->map[0]) || close_up_down(game->map[len - 1])
		|| (left == 1) || close_right(game->map))
		print_error("Map is not closed");
	if (valid_way(game->map))
		print_error("Invalid map : Space or tab found inside map");
}
