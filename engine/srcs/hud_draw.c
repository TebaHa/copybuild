/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 10:59:30 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/24 12:48:42 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_render_hud_stats(t_engine *eng, t_player *plr)
{
	SDL_Surface		*txt;
	char			*buff;

	buff = ft_itoa(plr->health);
	txt = create_text(eng, buff, 0xFFFFFFFF);
	free(buff);
	draw_player_stats(eng, txt, (t_point_2d){80, HEIGHT - 50});
	buff = ft_itoa(plr->armor);
	txt = create_text(eng, buff, 0xFFFFFFFF);
	free(buff);
	draw_player_stats(eng, txt, (t_point_2d){80, HEIGHT - 130});
	buff = ft_itoa(plr->wpn->ammo);
	txt = create_text(eng, buff, 0xFFFFFFFF);
	free(buff);
	draw_player_stats(eng, txt, (t_point_2d){WIDTH - 100,
	HEIGHT - 50});
}

void		engine_draw_hud(t_hud *hud, t_player *plr, SDL_Surface *surf)
{
	t_sprite		*img;

	bresenham_line(&(t_point_3d){0, (WIDTH / 2) - 10,
	(HEIGHT / 2), 0}, &(t_point_3d){0, (WIDTH / 2) + 10,
	(HEIGHT / 2), 0}, surf, get_rgb(0, 0, 0, 255));
	bresenham_line(&(t_point_3d){0, (WIDTH / 2),
	(HEIGHT / 2) - 10, 0}, &(t_point_3d){0, (WIDTH / 2),
	(HEIGHT / 2) + 10, 0}, surf, get_rgb(0, 0, 0, 255));
	img = plr->wpn->anmtn[plr->wpn->state];
	if (img->a_state == ANIMATE)
	{
		if (((plr->anim % img->frames_delay) == 0)
		&& (plr->frame_num < img->frames_num))
			plr->frame_num++;
		if (plr->frame_num == img->frames_num)
			plr->frame_num = 0;
	}
	//SDL_UnlockSurface(surf);
	hud = 0;
	draw_from_surface_to_surface(surf, img->surface[plr->frame_num],
	(WIDTH - img->surface[plr->frame_num]->w)
	/ 2, HEIGHT - img->surface[plr->frame_num]->h);
	//SDL_LockSurface(surf);
	plr->anim++;
}

void		draw_player_stats(t_engine *eng, SDL_Surface *txt,
			t_point_2d place)
{
	int			tex_w;
	int			tex_h;
	SDL_Texture	*tex;
	SDL_Rect	destrect;

	tex = SDL_CreateTextureFromSurface(eng->ren, txt);
	SDL_QueryTexture(tex, NULL, NULL, &tex_w, &tex_h);
	destrect = (SDL_Rect){place.x, place.y, tex_w, tex_h};
	SDL_RenderCopy(eng->ren, tex, NULL, &destrect);
	SDL_DestroyTexture(tex);
	SDL_FreeSurface(txt);
}

void		draw_from_surface_to_surface(SDL_Surface *dest,
			SDL_Surface *src, int dx, int dy)
{
	t_surf_data	data;

	data.x = 0;
	data.pix = (int *)dest->pixels;
	data.tx = dx;
	while (data.x < src->w && data.tx < dest->w)
	{
		data.y = 0;
		data.ty = dy;
		while (data.y < src->h && data.ty < dest->h)
			draw_from_s_to_s_help_1(&data, src);
		data.tx++;
		data.x++;
	}
}
