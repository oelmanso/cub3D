/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 23:42:39 by zhassna           #+#    #+#             */
/*   Updated: 2026/01/02 21:58:59 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_close(t_game *g)
{
	ft_finish(g);
	exit(0);
	return (0);
}

void	ft_finish(t_game *g)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (g->textures[i].img)
			mlx_destroy_image(g->frame.mlx, g->textures[i].img);
		i++;
	}
	if (g->frame.img)
		mlx_destroy_image(g->frame.mlx, g->frame.img);
	if (g->frame.win)
		mlx_destroy_window(g->frame.mlx, g->frame.win);
	if (g->frame.mlx)
	{
		mlx_destroy_display(g->frame.mlx);
		free(g->frame.mlx);
	}
	free_all(gc_instance());
}

int	key_press(int keycode, t_game *g)
{
	if (keycode == KEY_ESC)
		ft_close(g);
	if (keycode == KEY_W)
		g->keys.w = 1;
	else if (keycode == KEY_S)
		g->keys.s = 1;
	else if (keycode == KEY_A)
		g->keys.a = 1;
	else if (keycode == KEY_D)
		g->keys.d = 1;
	else if (keycode == KEY_LEFT)
		g->keys.left = 1;
	else if (keycode == KEY_RIGHT)
		g->keys.right = 1;
	return (0);
}

int	key_release(int keycode, t_game *g)
{
	if (keycode == KEY_W)
		g->keys.w = 0;
	else if (keycode == KEY_S)
		g->keys.s = 0;
	else if (keycode == KEY_A)
		g->keys.a = 0;
	else if (keycode == KEY_D)
		g->keys.d = 0;
	else if (keycode == KEY_LEFT)
		g->keys.left = 0;
	else if (keycode == KEY_RIGHT)
		g->keys.right = 0;
	return (0);
}
