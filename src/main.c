/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:38:58 by zhassna           #+#    #+#             */
/*   Updated: 2026/01/02 22:39:17 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_garbage_collector	**gc_instance(void)
{
	static t_garbage_collector	*gc = NULL;

	return (&gc);
}

int	main(int ac, char **av)
{
	t_game	g;

	parse_cub(&g, ac, av);
	init_player(&g, g.map);
	g.frame.mlx = mlx_init();
	g.frame.win = mlx_new_window(g.frame.mlx, WIDTH, HEIGHT, "cub3d");
	g.frame.img = mlx_new_image(g.frame.mlx, WIDTH, HEIGHT);
	g.frame.addr = mlx_get_data_addr(g.frame.img, &g.frame.bpp,
			&g.frame.line_len, &g.frame.endian);
	if (!load_textures(&g))
		print_error1("Invalid texture");
	mlx_loop_hook(g.frame.mlx, render, &g);
	mlx_hook(g.frame.win, KeyPress, KeyPressMask, key_press, &g);
	mlx_hook(g.frame.win, KeyRelease, KeyReleaseMask, key_release, &g);
	mlx_hook(g.frame.win, 17, 0, ft_close, &g);
	mlx_loop(g.frame.mlx);
	free_all(gc_instance());
	return (0);
}
