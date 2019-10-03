/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 10:59:30 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/03 06:00:13 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

void		engine_draw_hud(t_engine *eng, t_player *plr, SDL_Surface *surf)
{
	int				i;
	int				x;
	int				y;
	int				tx;
	int				ty;
	int				*pix;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned char	alpha;
	t_sprite		*img;

	i = 0;
	bresenham_line(&(t_point_3d){0, (WIDTH / 2) - 10, (HEIGHT / 2), 0}, &(t_point_3d){0, (WIDTH / 2) + 10, (HEIGHT / 2), 0}, surf, get_rgb(255, 255, 255, 255));
	bresenham_line(&(t_point_3d){0, (WIDTH / 2), (HEIGHT / 2) - 10, 0}, &(t_point_3d){0, (WIDTH / 2), (HEIGHT / 2) + 10, 0}, surf, get_rgb(255, 255, 255, 255));
	pix = (int *)surf->pixels;
	img = plr->wpn->anmtn[plr->wpn->state];
	x = 0;
	tx = (WIDTH - img->surface->w) / 2;
	while (x < img->surface->w)
	{
		y = 0;
		ty = HEIGHT - img->surface->h;
		while (y < img->surface->h)
		{
			alpha = ((unsigned char *)img->surface->pixels)[(y * 4 * img->surface->w + x * 4) + 3];
			if (alpha == 255)
			{
				red = ((unsigned char *)img->surface->pixels)[(y * 4 * img->surface->w + x * 4)];
				green = ((unsigned char *)img->surface->pixels)[(y * 4 * img->surface->w + x * 4) + 1];
				blue = ((unsigned char *)img->surface->pixels)[(y * 4 * img->surface->w + x * 4) + 2];
				pix[ty * WIDTH + tx] = get_rgb(red, green, blue, 255);
			}
			y++;
			ty++;
		}
		tx++;
		x++;
	}
	plr->anim++;
}
