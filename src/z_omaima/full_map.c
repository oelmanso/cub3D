/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 11:00:23 by oelmanso          #+#    #+#             */
/*   Updated: 2025/12/28 11:00:54 by oelmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub.h"

void	print_error(char *msg)
{
	free_all(gc_instance());
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}

void	alloc_map(t_game *game, int len, int lng)
{
	int	i;

	i = 0;
	game->map = malloc(sizeof(char *) * (len + 1));
	if (!game->map)
		print_error("malloc failed");
	gc_add_node_back(gc_instance(), gc_new_node(game->map));
	while (i < len)
		game->map[i++] = strdup_map(game->all_map[game->map_start++], lng);
	game->map[i] = NULL;
}

void	pos_player(t_game *game)
{
	if (game->flag_pos)
		print_error("Duplicate player");
	game->flag_pos = 1;
}

int	calcul_long(t_game *game, char **map)
{
	int	lng;
	int	len;
	int	j;

	len = 0;
	lng = ft_strlen(map[0]);
	while (map[len])
	{
		j = 0;
		while (map[len][j])
		{
			if (check_player(map[len][j]))
				pos_player(game);
			if (!valide_elem(map[len][j]))
				print_error("Invalid element on the map!");
			j++;
		}
		if (lng < ft_strlen(map[len]))
			lng = ft_strlen(map[len]);
		len++;
	}
	if (!game->flag_pos)
		print_error("No player");
	game->length_map = len;
	return (lng);
}

void	full_map(t_game *game)
{
	int	i;
	int	start;
	int	lng;

	start = game->map_start;
	lng = calcul_long(game, &game->all_map[start]);
	game->width_map = lng;
	while (game->length_map > 0)
	{
		i = 0;
		while (whitespace(game->all_map[start + game->length_map - 1][i]))
			i++;
		if (game->all_map[start + game->length_map - 1][i] != '\0')
			break ;
		game->length_map--;
	}
	alloc_map(game, game->length_map, lng);
}
