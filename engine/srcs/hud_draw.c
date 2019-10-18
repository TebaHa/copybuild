/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 10:59:30 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/18 19:59:06 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_render_hud_stats(t_engine *eng,
			t_player *plr, SDL_Surface *surf)
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
	draw_player_stats(eng, surf, hp, armor);
}

void		engine_draw_hud(t_engine *eng, t_player *plr, SDL_Surface *surf)
{
	int				i;
	t_sprite		*img;
	SDL_Surface		*hp;
	SDL_Surface		*armor;

	i = 0;
	bresenham_line(&(t_point_3d){0, (WIDTH / 2) - 10,
	(HEIGHT / 2), 0}, &(t_point_3d){0, (WIDTH / 2) + 10,
	(HEIGHT / 2), 0}, surf, get_rgb(255, 255, 255, 255));
	bresenham_line(&(t_point_3d){0, (WIDTH / 2),
	(HEIGHT / 2) - 10, 0}, &(t_point_3d){0, (WIDTH / 2),
	(HEIGHT / 2) + 10, 0}, surf, get_rgb(255, 255, 255, 255));
	img = plr->wpn->anmtn[plr->wpn->state];
	if (img->a_state != STATIC)
	{
		if (((plr->anim % img->frames_delay
		/ 2) == 0) && (plr->frame_num < img->frames_num - 1))
			plr->frame_num++;
		if (plr->frame_num == img->frames_num - 1)
			plr->frame_num = 0;
	}
	draw_from_surface_to_surface(surf, img->surface[plr->frame_num],
	(WIDTH - img->surface[plr->frame_num]->w)
	/ 2, HEIGHT - img->surface[plr->frame_num]->h);
	plr->anim++;
}

void		draw_player_stats(t_engine *eng,
			SDL_Surface *surf, SDL_Surface *hp, SDL_Surface *armor)
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
		data.y = 0;
		data.ty = dy;
		while (data.y < dest->h)
		{
			data.alpha = ((unsigned char *)src->pixels)
			[(data.y * 4 * src->w + data.x * 4) + 3];
			if (data.alpha == 255)
			{
				draw_from_s_to_s_help(&data, src);
			}
			data.y++;
			data.ty++;
		}
		data.tx++;
		data.x++;
	}
}

void		draw_from_s_to_s_help(t_surf_data *data, SDL_Surface *src)
{
	data->red = ((unsigned char *)src->pixels)
	[(data->y * 4 * src->w + data->x * 4)];
	data->green = ((unsigned char *)src->pixels)
	[(data->y * 4 * src->w + data->x * 4) + 1];
	data->blue = ((unsigned char *)src->pixels)
	[(data->y * 4 * src->w + data->x * 4) + 2];
	data->pix[data->ty * WIDTH + data->tx] =
	get_rgb(data->red, data->green, data->blue, 255);
}
