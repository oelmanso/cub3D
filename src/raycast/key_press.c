/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 16:01:10 by zhassna           #+#    #+#             */
/*   Updated: 2025/12/21 17:31:13 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	turn_left_right(t_game *g, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = g->player.dirx;
	old_planex = g->player.planex;
	g->player.dirx = g->player.dirx * cos(angle) - g->player.diry * sin(angle);
	g->player.diry = old_dirx * sin(angle) + g->player.diry * cos(angle);
	g->player.planex = g->player.planex * cos(angle) - g->player.planey
		* sin(angle);
	g->player.planey = old_planex * sin(angle) + g->player.planey * cos(angle);
}

void	key_a_d(t_game *g, double sx, double sy)
{
	if (g->map[(int)(g->player.posy)][(int)(g->player.posx + sx
			* g->move_speed)] == '0')
		g->player.posx += sx * g->move_speed;
	if (g->map[(int)(g->player.posy + sy
			* g->move_speed)][(int)(g->player.posx)] == '0')
		g->player.posy += sy * g->move_speed;
}

void	key_move2(t_game *g)
{
	if (g->keys.a)
		key_a_d(g, g->player.diry, -g->player.dirx);
	if (g->keys.d)
		key_a_d(g, -g->player.diry, g->player.dirx);
	if (g->keys.right)
		turn_left_right(g, g->rot_speed);
	if (g->keys.left)
		turn_left_right(g, -g->rot_speed);
}

int	key_move(t_game *g)
{
	if (g->keys.w)
	{
		if (g->map[(int)(g->player.posy)][(int)(g->player.posx + g->player.dirx
				* g->move_speed)] == '0')
			g->player.posx += g->player.dirx * g->move_speed;
		if (g->map[(int)(g->player.posy + g->player.diry
				* g->move_speed)][(int)(g->player.posx)] == '0')
			g->player.posy += g->player.diry * g->move_speed;
	}
	if (g->keys.s)
	{
		if (g->map[(int)(g->player.posy)][(int)(g->player.posx - g->player.dirx
				* g->move_speed)] == '0')
			g->player.posx -= g->player.dirx * g->move_speed;
		if (g->map[(int)(g->player.posy - g->player.diry
				* g->move_speed)][(int)(g->player.posx)] == '0')
			g->player.posy -= g->player.diry * g->move_speed;
	}
	key_move2(g);
	return (0);
}
