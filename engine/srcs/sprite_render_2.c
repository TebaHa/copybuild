/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 21:37:00 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/19 22:57:05 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_render_sprites_in_sector_1(t_sector *sect, SDL_Surface *surf,
			t_player *plr, t_sprt_r *d)
{
	d->spritex = sect->sprobjects_array[sect->order[d->i]].position.x
	- plr->position.x;
	d->spritey = sect->sprobjects_array[sect->order[d->i]].position.y
	- plr->position.y;
	d->dirx = d->spritex * plr->sinangle - d->spritey * plr->cosangle;
	d->diry = d->spritex * plr->cosangle + d->spritey * plr->sinangle;
	d->stry = d->dirx + (float)sect->sprobjects_array[sect->order[d->i]].
	type->anmtn[0]->surface[0]->w * 0.25;
	d->endy = d->dirx - (float)sect->sprobjects_array[sect->order[d->i]].
	type->anmtn[0]->surface[0]->w * 0.25;
}

void		engine_render_sprites_in_sector_2(t_sector *sect, SDL_Surface *surf,
			t_player *plr, t_sprt_r *d)
{
	d->scaledx = WIDTH * HFOV / d->diry;
	d->scaledy = HEIGHT * VFOV / d->diry;
	d->x1 = WIDTH / 2 - (int)((d->stry) * d->scaledx);
	d->x2 = WIDTH / 2 - (int)((d->endy) * d->scaledx);
}

void		engine_render_sprites_in_sector_3(t_sector *sect, SDL_Surface *surf,
			t_player *plr, t_sprt_r *d)
{
	d->ceil = sect->floor + sect->sprobjects_array[sect->order[d->i]].
	type->anmtn[0]->surface[0]->h * 1.5 - plr->position.z;
	d->floor = sect->floor - plr->position.z;
	d->ya = HEIGHT / 2 - (int)((d->ceil + d->diry * plr->yaw) * d->scaledy);
	d->yb = HEIGHT / 2 - (int)((d->floor + d->diry * plr->yaw) * d->scaledy);
}

void		engine_render_sprites_in_sector_4(t_sector *sect, SDL_Surface *surf,
			t_player *plr, t_sprt_r *d)
{
	d->txtx = (int)((float)(d->x - d->x1) /
	(float)(d->x2 - d->x1) * sect->sprobjects_array[sect->order[d->i]].
	type->anmtn[0]->surface[0]->w);
	engine_vline_textured_surface(surf,
	(t_scaler)scaler_init((float[5]){d->ya, d->cya, d->yb, 0,
	sect->sprobjects_array[sect->order[d->i]].
	type->anmtn[0]->surface[0]->h - 1})
	, (t_vline1_in){(t_fix_point_3d){d->x, d->cya + 1, 0},
	(t_fix_point_3d){d->x, d->cyb, 0}, d->txtx},
	sect->sprobjects_array[sect->order[d->i]].type->anmtn[0]->surface[0]);
	d->x++;
}
