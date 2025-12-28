/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oelmanso <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 11:04:25 by oelmanso          #+#    #+#             */
/*   Updated: 2025/12/28 11:05:00 by oelmanso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	draw_minimap(t_game *g)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->length_map)
	{
		x = 0;
		while (x < g->width_map)
		{
			if (g->map[y][x] == '1')
				draw_square(g, MINI_X + x * MINI_TILE, MINI_Y + y * MINI_TILE,
					MINI_TILE, 0x848482);
			else if (g->map[y][x] == '0')
				draw_square(g, MINI_X + x * MINI_TILE, MINI_Y + y * MINI_TILE,
					MINI_TILE, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void	draw_square(t_game *g, int x, int y, int size, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(&g->frame, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_player_minimap(t_game *g)
{
	int	x;
	int	y;

	x = MINI_X + g->player.posX * MINI_TILE;
	y = MINI_Y + g->player.posY * MINI_TILE;
	draw_square(g, x - 2, y - 2, 4, 0x000080);
}

void	draw_player_dir(t_game *g)
{
	double	len;
	double	step;
	double	start_x;
	double	start_y;
	double	player_half;
	int		x;
	int		y;

	player_half = 3.0 / MINI_TILE;
	start_x = g->player.posX + g->player.dirX * player_half;
	start_y = g->player.posY + g->player.dirY * player_half;
	len = 0.0;
	step = 0.05;
	while (len < 0.6)
	{
		x = MINI_X + (start_x + g->player.dirX * len) * MINI_TILE;
		y = MINI_Y + (start_y + g->player.dirY * len) * MINI_TILE;
		my_mlx_pixel_put(&g->frame, x, y, 0xD3AE36);
		len += step;
	}
}

int	render(t_game *g)
{
	game_loop(g);
	draw_minimap(g);
	draw_player_minimap(g);
	draw_player_dir(g);
	mlx_put_image_to_window(g->frame.mlx, g->frame.win, g->frame.img, 0, 0);
	return (0);
}
