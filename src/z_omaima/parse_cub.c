/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 10:56:38 by oelmanso          #+#    #+#             */
/*   Updated: 2025/12/28 10:57:07 by oelmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../cub.h"

void	error_textur(char *msg, char *s)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, " : ", 3);
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	free_all(gc_instance());
	exit(1);
}

void	init(t_game *game)
{
	game->flag_pos = 0;
	game->textures[NO].path = NULL;
	game->textures[NO].flag = 0;
	game->textures[SO].path = NULL;
	game->textures[SO].flag = 0;
	game->textures[WE].path = NULL;
	game->textures[WE].flag = 0;
	game->textures[EA].path = NULL;
	game->textures[EA].flag = 0;
	game->floor_color.flage = 0;
	game->ceiling_color.flage = 0;
}

int	check_name(char *av, char *p)
{
	int	i;

	i = 0;
	while (av[i])
	{
		if (ft_strncmp(&av[i], p, 4) == 0)
		{
			if (i == 0)
				break ;
			if (!av[i + 4])
				return (0);
			else
				break ;
		}
		i++;
	}
	return (1);
}

void	read_map(t_game *game, char **av)
{
	char	*line;
	char	*join;
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		print_error("Cannot open file");
	join = NULL;
	line = get_next_line(fd);
	while (line)
	{
		join = ft_strjoin(join, line);
		line = get_next_line(fd);
	}
	game->all_map = ft_split(join, '\n');
	if (!game->all_map)
		print_error("Empty file");
	parse_cub_file(game);
}

void	parse_cub(t_game *game, int ac, char **av)
{
	if (ac > 2 || ac < 2)
		print_error("Invalid arguments");
	if (check_name(av[1], ".cub"))
		print_error("Invalid file extension");
	init(game);
	read_map(game, av);
}
