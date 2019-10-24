/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 10:59:30 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/24 01:52:47 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_render_hud_stats(t_engine *eng, t_player *plr)
{
	SDL_Surface		*hp;
	SDL_Surface		*armor;
	char			*buff;

	buff = ft_itoa(plr->health);
	hp = create_text(eng, buff, 0xE9967AFF);
	free(buff);
	buff = ft_itoa(plr->armor);
	armor = create_text(eng, buff, 0xE9967AFF);
	free(buff);
	draw_player_stats(eng, hp, armor);
}

void		engine_draw_hud(t_player *plr, SDL_Surface *surf)
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
	draw_from_surface_to_surface(surf, img->surface[plr->frame_num],
	(WIDTH - img->surface[plr->frame_num]->w)
	/ 2, HEIGHT - img->surface[plr->frame_num]->h);
	plr->anim++;
}

void		draw_player_stats(t_engine *eng, SDL_Surface *hp,
			SDL_Surface *armor)
{
	int			tex_w;
	int			tex_h;
	SDL_Texture	*tex_hp;
	SDL_Texture	*tex_armor;
	SDL_Rect	destrect;

	tex_hp = SDL_CreateTextureFromSurface(eng->ren, hp);
	tex_armor = SDL_CreateTextureFromSurface(eng->ren, armor);
	SDL_QueryTexture(tex_hp, NULL, NULL, &tex_w, &tex_h);
	destrect = (SDL_Rect){20, HEIGHT - 60, tex_w, tex_h};
	SDL_RenderCopy(eng->ren, tex_hp, NULL, &destrect);
	SDL_QueryTexture(tex_armor, NULL, NULL, &tex_w, &tex_h);
	destrect = (SDL_Rect){20, HEIGHT - 40, tex_w, tex_h};
	SDL_RenderCopy(eng->ren, tex_armor, NULL, &destrect);
	SDL_DestroyTexture(tex_hp);
	SDL_DestroyTexture(tex_armor);
	SDL_FreeSurface(hp);
	SDL_FreeSurface(armor);
}

void		draw_from_surface_to_surface(SDL_Surface *dest,
			SDL_Surface *src, int dx, int dy)
{
	t_surf_data	data;

	data.x = 0;
	data.pix = (int *)dest->pixels;
	data.tx = dx;
	while (data.x < dest->w)
	{
		if (data.tx >= 0 && data.tx <= WIDTH)
		{
			data.y = 0;
			data.ty = dy;
			while (data.y < dest->h)
				draw_from_s_to_s_help_1(&data, src);
		}
		data.tx++;
		data.x++;
	}
}
