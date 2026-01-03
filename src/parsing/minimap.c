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

	if ((MINI_X + (g->width_map * MINI_TILE) >= WIDTH) || (MINI_Y
			+ (g->length_map * MINI_TILE) >= HEIGHT))
	{
		ft_finish(g);
		print_error1("MINI_TILE is too large");
	}
	y = 0;
	while (y < g->length_map)
	{
		x = 0;
		while (x < g->width_map)
		{
			if (g->map[y][x] == '1')
				draw_square(g, MINI_X + x * MINI_TILE, MINI_Y + y * MINI_TILE,
					2);
			else if (g->map[y][x] == '0')
				draw_square(g, MINI_X + x * MINI_TILE, MINI_Y + y * MINI_TILE,
					3);
			x++;
		}
		y++;
	}
}

void	draw_square(t_game *g, int x, int y, int c)
{
	int	i;
	int	j;
	int	size;
	int	color;

	i = 0;
	size = ft_size(c);
	color = ft_color(c);
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

	x = MINI_X + g->player.posx * MINI_TILE;
	y = MINI_Y + g->player.posy * MINI_TILE;
	draw_square(g, x - 3, y - 3, 1);
}

void	draw_player_dir(t_game *g)
{
	double	len;
	double	start_x;
	double	start_y;
	int		x;
	int		y;

	start_x = g->player.posx + g->player.dirx * (3.0 / MINI_TILE);
	start_y = g->player.posy + g->player.diry * (3.0 / MINI_TILE);
	len = 0.0;
	while (len < 1)
	{
		x = MINI_X + (start_x + g->player.dirx * len) * MINI_TILE;
		y = MINI_Y + (start_y + g->player.diry * len) * MINI_TILE;
		my_mlx_pixel_put(&g->frame, x, y, 0xD3AE36);
		len += 0.05;
	}
}

int	render(t_game *g)
{
	key_move(g);
	raycaster(g);
	draw_minimap(g);
	draw_player_minimap(g);
	draw_player_dir(g);
	mlx_put_image_to_window(g->frame.mlx, g->frame.win, g->frame.img, 0, 0);
	return (0);
}
