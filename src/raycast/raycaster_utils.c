/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zhassna <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 17:22:04 by zhassna           #+#    #+#             */
/*   Updated: 2025/12/21 17:23:49 by zhassna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static int	get_texcolor(t_game *g, int tex, int tx, int ty)
{
	char	*pixel;

	pixel = g->textures[tex].addr + (ty * g->textures[tex].line_len + tx
			* (g->textures[tex].bpp / 8));
	return (*(unsigned int *)pixel);
}

void	get_texture_color(t_game *g, t_box *box, int x, int y)
{
	box->texy = (int)box->texpos;
	if (box->texy < 0)
		box->texy = 0;
	if (box->texy >= g->textures[box->texnum].h)
		box->texy = g->textures[box->texnum].h - 1;
	box->texpos += box->step;
	box->color = get_texcolor(g, box->texnum, box->texx, box->texy);
	if (box->side == 1)
		box->color = (box->color >> 1) & 0x7F7F7F;
	my_mlx_pixel_put(&g->frame, x, y, box->color);
}

void	texture(t_game *g, t_box *box)
{
	if (box->side == 0 && box->raydirx > 0)
		box->texnum = 3;
	else if (box->side == 0 && box->raydirx < 0)
		box->texnum = 2;
	else if (box->side == 1 && box->raydiry > 0)
		box->texnum = 1;
	else
		box->texnum = 0;
	if (box->side == 0)
		box->wallx = g->player.posy + box->perpwalldist * box->raydiry;
	else
		box->wallx = g->player.posx + box->perpwalldist * box->raydirx;
	box->wallx -= floor(box->wallx);
	box->texx = (int)(box->wallx * g->textures[box->texnum].w);
	if (box->side == 0 && box->raydirx < 0)
		box->texx = g->textures[box->texnum].w - box->texx - 1;
	if (box->side == 1 && box->raydiry > 0)
		box->texx = g->textures[box->texnum].w - box->texx - 1;
	box->step = 1.0 * g->textures[box->texnum].h / box->lineheight;
	box->texpos = (box->drawstart - HEIGHT / 2 + box->lineheight / 2)
		* box->step;
}

void	distance(t_game *g, t_box *box)
{
	if (box->side == 0)
		box->perpwalldist = (box->mapx - g->player.posx + (1 - box->stepx)
				/ 2.0) / box->raydirx;
	else
		box->perpwalldist = (box->mapy - g->player.posy + (1 - box->stepy)
				/ 2.0) / box->raydiry;
	box->lineheight = (int)(HEIGHT / box->perpwalldist);
	box->drawstart = -box->lineheight / 2 + HEIGHT / 2;
	box->drawend = box->lineheight / 2 + HEIGHT / 2;
	if (box->drawstart < 0)
		box->drawstart = 0;
	if (box->drawend >= HEIGHT)
		box->drawend = HEIGHT - 1;
	texture(g, box);
}
