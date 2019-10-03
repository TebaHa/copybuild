/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 10:59:30 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/03 07:33:50 by zytrams          ###   ########.fr       */
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
	SDL_Surface		*surfs;

	i = 0;
	bresenham_line(&(t_point_3d){0, (WIDTH / 2) - 10, (HEIGHT / 2), 0}, &(t_point_3d){0, (WIDTH / 2) + 10, (HEIGHT / 2), 0}, surf, get_rgb(255, 255, 255, 255));
	bresenham_line(&(t_point_3d){0, (WIDTH / 2), (HEIGHT / 2) - 10, 0}, &(t_point_3d){0, (WIDTH / 2), (HEIGHT / 2) + 10, 0}, surf, get_rgb(255, 255, 255, 255));
	pix = (int *)surf->pixels;
	img = plr->wpn->anmtn[plr->wpn->state];
	if (img->a_state != STATIC)
	{
		if (img->a_state == ANIMATE)
		{
			if (((plr->anim % img->frames_delay) == 0) && (plr->frame_num < img->frames_num - 1))
				plr->frame_num++;
		}
		if (img->a_state == CYCLE)
		{
			if (((plr->anim % img->frames_delay) == 0) && (plr->frame_num < img->frames_num - 1))
				plr->frame_num++;
			if (plr->frame_num == img->frames_num - 1)
				plr->frame_num = 0;
		}
	}
	//printf("%d %d\n", img->frames_num, plr->frame_num);
	surfs = &img->surface[plr->frame_num];
	x = 0;
	tx = (WIDTH - surfs->w) / 2;
	while (x < surfs->w)
	{
		y = 0;
		ty = HEIGHT - surfs->h;
		while (y < surfs->h)
		{
			alpha = ((unsigned char *)surfs->pixels)[(y * 4 * surfs->w + x * 4) + 3];
			if (alpha == 255)
			{
				red = ((unsigned char *)surfs->pixels)[(y * 4 * surfs->w + x * 4)];
				green = ((unsigned char *)surfs->pixels)[(y * 4 * surfs->w + x * 4) + 1];
				blue = ((unsigned char *)surfs->pixels)[(y * 4 * surfs->w + x * 4) + 2];
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
