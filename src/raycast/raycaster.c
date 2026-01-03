/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:19:40 by zhassna           #+#    #+#             */
/*   Updated: 2026/01/02 21:59:22 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	dda(t_game *g, t_box *box)
{
	box->hit = 0;
	box->side = 0;
	while (!box->hit)
	{
		if (box->sidedistx < box->sidedisty)
		{
			box->sidedistx += box->deltadistx;
			box->mapx += box->stepx;
			box->side = 0;
		}
		else
		{
			box->sidedisty += box->deltadisty;
			box->mapy += box->stepy;
			box->side = 1;
		}
		if (box->mapx < 0 || box->mapx >= g->width_map || box->mapy < 0
			|| box->mapy >= g->length_map)
			box->hit = 1;
		if (g->map[box->mapy][box->mapx] == '1')
			box->hit = 1;
	}
	distance(g, box);
}

void	perform_dda(t_game *g, t_box *box)
{
	if (box->raydiry < 0)
	{
		box->stepy = -1;
		box->sidedisty = (g->player.posy - box->mapy) * box->deltadisty;
	}
	else
	{
		box->stepy = 1;
		box->sidedisty = (box->mapy + 1.0 - g->player.posy) * box->deltadisty;
	}
	dda(g, box);
}

void	ray_setup(t_game *g, t_box *box)
{
	box->mapx = (int)g->player.posx;
	box->mapy = (int)g->player.posy;
	box->raydirx = g->player.dirx + g->player.planex * box->camerax;
	box->raydiry = g->player.diry + g->player.planey * box->camerax;
	if (box->raydirx == 0)
		box->deltadistx = 1e30;
	else
		box->deltadistx = fabs(1 / box->raydirx);
	if (box->raydiry == 0)
		box->deltadisty = 1e30;
	else
		box->deltadisty = fabs(1 / box->raydiry);
	if (box->raydirx < 0)
	{
		box->stepx = -1;
		box->sidedistx = (g->player.posx - box->mapx) * box->deltadistx;
	}
	else
	{
		box->stepx = 1;
		box->sidedistx = (box->mapx + 1.0 - g->player.posx) * box->deltadistx;
	}
	perform_dda(g, box);
}

int	raycaster(t_game *g)
{
	t_box	box;
	int		x;
	int		y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		box.camerax = 2.0 * x / (double)WIDTH - 1.0;
		ray_setup(g, &box);
		while (y < HEIGHT)
		{
			if (y < box.drawstart)
				my_mlx_pixel_put(&g->frame, x, y, g->ceiling_color.value);
			else if (y > box.drawend)
				my_mlx_pixel_put(&g->frame, x, y, g->floor_color.value);
			else
				get_texture_color(g, &box, x, y);
			y++;
		}
		x++;
	}
	return (0);
}
