/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_t.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 10:57:30 by oelmanso          #+#    #+#             */
/*   Updated: 2025/12/28 10:58:08 by oelmanso         ###   ########.fr       */
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

int	check_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	return (0);
}

int	valid_number(char *line)
{
	int	nmb;

	nmb = ft_atoi(line);
	if (nmb < 0 || nmb > 255)
		print_error("Color out of range");
	return (nmb);
}

void	is_map_last(t_game *game, int i)
{
	if (!game->textures[NO].flag || !game->textures[SO].flag
		|| !game->textures[WE].flag || !game->textures[EA].flag
		|| !game->floor_color.flage || !game->ceiling_color.flage)
	{
		print_error("Invalid file structure");
	}
	game->map_start = i;
}
