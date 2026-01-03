/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:00:12 by zhassna           #+#    #+#             */
/*   Updated: 2026/01/02 22:07:59 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	set_pdir2(t_game *game, char c)
{
	if (c == 'E')
	{
		game->player.dirx = 1;
		game->player.diry = 0;
		game->player.planex = 0;
		game->player.planey = game->player.fov;
	}
	else if (c == 'W')
	{
		game->player.dirx = -1;
		game->player.diry = 0;
		game->player.planex = 0;
		game->player.planey = -game->player.fov;
	}
}

void	set_pdir(t_game *game, char c)
{
	ft_bzero(&game->keys, sizeof(t_keys));
	game->rot_speed = ROT_SPEED;
	game->move_speed = MOVE_SPEED;
	if (c == 'N')
	{
		game->player.dirx = 0;
		game->player.diry = -1;
		game->player.planex = game->player.fov;
		game->player.planey = 0;
	}
	else if (c == 'S')
	{
		game->player.dirx = 0;
		game->player.diry = 1;
		game->player.planex = -game->player.fov;
		game->player.planey = 0;
	}
	set_pdir2(game, c);
}

void	init_player(t_game *game, char **map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	x = 0;
	game->player.fov = tan(FOV_DEG * M_PI / 360.0);
	// printf("player fov how [%f]==========\n", game->player.fov);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			c = map[y][x];
			if (map[y][x] == '\r')
			{
				printf("-----found '\\r' in map\n\n");
				map[y][x] = '\0';
			}
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player.posx = x + 0.5;
				game->player.posy = y + 0.5;
				map[y][x] = '0';
				set_pdir(game, c);
				return ;
			}
			x++;
		}
		y++;
	}
}
