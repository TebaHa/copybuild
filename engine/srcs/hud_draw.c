/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 10:59:30 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/12 17:42:39 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

void		engine_render_hud_stats(t_engine *eng, t_player *plr, SDL_Surface *surf)
{
	SDL_Surface		*hp;
	SDL_Surface		*armor;

	hp = create_text(eng, ft_itoa(plr->health), (int)0xFFFFFFFF);
	armor = create_text(eng, ft_itoa(plr->armor), (int)0xFFFFFFFF);
	draw_player_stats(eng, surf, hp, armor);
}

void		engine_draw_hud(t_engine *eng, t_player *plr, SDL_Surface *surf)
{
	int				i;
	t_sprite		*img;
	SDL_Surface		*hp;
	SDL_Surface		*armor;

	i = 0;
	bresenham_line(&(t_point_3d){0, (WIDTH / 2) - 10, (HEIGHT / 2), 0}, &(t_point_3d){0, (WIDTH / 2) + 10, (HEIGHT / 2), 0}, surf, get_rgb(255, 255, 255, 255));
	bresenham_line(&(t_point_3d){0, (WIDTH / 2), (HEIGHT / 2) - 10, 0}, &(t_point_3d){0, (WIDTH / 2), (HEIGHT / 2) + 10, 0}, surf, get_rgb(255, 255, 255, 255));
	img = plr->wpn->anmtn[plr->wpn->state];
	if (img->a_state != STATIC)
	{
		if (((plr->anim % img->frames_delay / 2) == 0) && (plr->frame_num < img->frames_num - 1))
			plr->frame_num++;
		if (plr->frame_num == img->frames_num - 1)
			plr->frame_num = 0;
	}
	draw_from_surface_to_surface(surf, img->surface[plr->frame_num],
	(WIDTH - img->surface[plr->frame_num]->w) / 2, HEIGHT - img->surface[plr->frame_num]->h);
	plr->anim++;
}

void		draw_player_stats(t_engine *eng, SDL_Surface *surf, SDL_Surface *hp, SDL_Surface *armor)
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

void		draw_from_surface_to_surface(SDL_Surface *dest, SDL_Surface *src, int dx, int dy)
{
	int				*pix;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	unsigned char	alpha;
	int				tx;
	int				ty;
	int				x;
	int				y;

	x = 0;
	pix = (int *)dest->pixels;
	tx = dx;
	while (x < dest->w)
	{
		y = 0;
		ty = dy;
		while (y < dest->h)
		{
			alpha = ((unsigned char *)src->pixels)[(y * 4 * src->w + x * 4) + 3];
			if (alpha == 255)
			{
				red = ((unsigned char *)src->pixels)[(y * 4 * src->w + x * 4)];
				green = ((unsigned char *)src->pixels)[(y * 4 * src->w + x * 4) + 1];
				blue = ((unsigned char *)src->pixels)[(y * 4 * src->w + x * 4) + 2];
				pix[ty * WIDTH + tx] = get_rgb(red, green, blue, 255);
			}
			y++;
			ty++;
		}
		tx++;
		x++;
	}
}