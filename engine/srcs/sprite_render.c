/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 03:13:59 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 15:03:15 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int			engine_render_sprites_in_sector_wrap(t_sector *sect,
			t_player *plr, t_sprt_r *d)
{
	if (sect->sprobjects_array[sect->order[d->i]].norender == true)
	{
		d->i++;
		return (0);
	}
	engine_render_sprites_in_sector_1(sect, plr, d);
	if (d->diry <= 0.0000000000001)
	{
		d->i++;
		return (0);
	}
	engine_render_sprites_in_sector_2(d);
	return (1);
}

t_sprobject	*engine_render_sprites_in_sector(t_sector *sect,
			SDL_Surface *surf, t_player *plr, t_item_sprts *restr)
{
	t_sprt_r	d;
	t_sprobject	*aimed;

	aimed = NULL;
	sort_sprites(sect, plr);
	d.i = 0;
	while (d.i < sect->sprobjects_count)
	{
		if (engine_render_sprites_in_sector_wrap(sect, plr, &d) == 0)
			continue ;
		if (d.x1 > restr->sect_id.sx2 || d.x2 < restr->sect_id.sx1)
		{
			d.i++;
			continue ;
		}
		get_sprite_image(sect, plr, &d);
		if (engine_render_sprites_in_sector_3(sect, plr, &d) == 0)
		{
			d.i++;
			continue ;
		}
		engine_render_sprites_in_sector_help(sect, surf, &d, restr);
	}
	return (aimed);
}

void		engine_render_sprites_in_sector_help(t_sector *sect,
			SDL_Surface *surf, t_sprt_r *d, t_item_sprts *restr)
{
	t_sprobject	*aimed;

	d->begx = max(d->x1, restr->sect_id.sx1);
	d->endx = min(d->x2, restr->sect_id.sx2);
	d->x = d->begx;
	if (d->ya <= (HEIGHT / 2) + 5 && d->cyb >= (HEIGHT / 2) - 5
	&& d->begx <= (WIDTH / 2) + 5 && d->endx >= (WIDTH / 2) - 5)
		aimed = &sect->sprobjects_array[sect->order[d->i]];
	while (d->x < d->endx)
	{
		d->cya = clamp(d->ya, restr->ytop[d->x], restr->ybottom[d->x]);
		d->cyb = clamp(d->yb, restr->ytop[d->x], restr->ybottom[d->x]);
		engine_render_sprites_in_sector_4(sect, surf, d);
	}
	d->i++;
}

void		sort_sprites(t_sector *sect, t_player *plr)
{
	int	i;

	i = 0;
	while (i < sect->sprobjects_count)
	{
		sect->order[i] = i;
		sect->dist[i] = ((plr->position.x
		- sect->sprobjects_array[i].position.x)
		* (plr->position.x - sect->sprobjects_array[i].position.x)
		+ (plr->position.y - sect->sprobjects_array[i].position.y)
		* (plr->position.y - sect->sprobjects_array[i].position.y));
		i++;
	}
	sprite_comb_sort(sect);
}

void		get_sprite_image(t_sector *sect, t_player *plr,
			t_sprt_r *d)
{
	t_sprobject	*obj;

	obj = &sect->sprobjects_array[sect->order[d->i]];
	if (obj->type->rotatable == ROTATABLE)
		get_sprite_rotatable_obj(plr, obj, d);
	else
		get_sprite_anim_obj_std(plr, obj, d);
}
