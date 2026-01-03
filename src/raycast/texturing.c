/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:30:39 by zhassna           #+#    #+#             */
/*   Updated: 2026/01/02 22:10:56 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	get_texture_addresses(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bpp, &game->textures[i].line_len,
				&game->textures[i].endian);
		i++;
	}
	while (i < 4)
	{
		if (!game->textures[i].addr)
			return (0);
		i--;
	}
	return (1);
}

int	load_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->frame.mlx,
				game->textures[i].path, &game->textures[i].w,
				&game->textures[i].h);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		if (!game->textures[i].img)
			return (ft_finish(game), 0);
		i++;
	}
	if (!get_texture_addresses(game))
		return (ft_finish(game), 0);
	return (1);
}
