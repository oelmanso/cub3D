/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_texture_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 10:55:38 by oelmanso          #+#    #+#             */
/*   Updated: 2025/12/28 10:56:14 by oelmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub.h"

int	is_num(char *str)
{
	int		i;
	char	*s;

	s = ft_strtrim(str, " \t");
	if (!s[0])
		print_error("Invalid color format");
	i = 0;
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	parse_color(t_color *color, char *s)
{
	char	**line;
	int		i;

	if (!s || !s[0])
		print_error("Invalid color");
	i = 0;
	if (color->flage)
		print_error("Duplicate color");
	color->flage = 1;
	line = ft_split(s, ',');
	if (!line || !line[0] || !line[1] || !line[2] || line[3] || !line[0][0]
		|| !line[1][0] || !line[2][0])
		print_error("Invalid color format");
	while (line[i])
	{
		if (!is_num(line[i]))
			print_error("Invalid color");
		i++;
	}
	color->r = valid_number(line[0]);
	color->g = valid_number(line[1]);
	color->b = valid_number(line[2]);
	color->value = (color->r << 16) | (color->g << 8) | color->b;
	return (1);
}

void	parse_textur(t_texture *t, char *map)
{
	char	*s;

	if (t->flag)
		print_error("Duplicate textur");
	t->flag = 1;
	if (!map || !map[0])
		print_error("Invalid textur format");
	s = ft_strtrim(map, " \t");
	if (!s[0])
		print_error("Invalid textur format");
	if (check_name(s, ".xpm"))
		print_error("Invalid textur name");
	if (check_texture_path(s))
		error_textur("Invalid texture path", s);
	t->path = s;
}

int	texture_color(t_game *game, char *m, char c, int i)
{
	if (ft_strncmp(m, "NO ", 3) == 0)
		parse_textur(&game->textures[NO], m + 3);
	else if (ft_strncmp(m, "SO ", 3) == 0)
		parse_textur(&game->textures[SO], m + 3);
	else if (ft_strncmp(m, "WE ", 3) == 0)
		parse_textur(&game->textures[WE], m + 3);
	else if (ft_strncmp(m, "EA ", 3) == 0)
		parse_textur(&game->textures[EA], m + 3);
	else if (ft_strncmp(m, "F ", 2) == 0)
		parse_color(&game->floor_color, m + 2);
	else if (ft_strncmp(m, "C ", 2) == 0)
		parse_color(&game->ceiling_color, m + 2);
	else if (c == '0' || c == '1')
		return (is_map_last(game, i), 0);
	else if (c != '\0')
		print_error("Unknown element");
	return (1);
}

int	check_parse_file(t_game *game)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (game->all_map[i])
	{
		j = 0;
		while (whitespace(game->all_map[i][j]))
			j++;
		c = game->all_map[i][j];
		if (!texture_color(game, &game->all_map[i][j], c, i))
			return (0);
		i++;
	}
	return (1);
}
