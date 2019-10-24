/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 03:13:59 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/24 03:44:59 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_render_sprites(t_engine *eng, t_player *plr,
			SDL_Surface *surf)
{
	t_item_sprts	*restr;
	t_sector		*sect;

	while (((restr = engine_pop_spriterenderstack(eng->world->
	sprite_renderstack)) != NULL))
	{
		sect = eng->world->sectors_array + restr->sect_id.sectorno;
		engine_render_sprites_in_sector(sect, surf, plr, restr);
	}
}

int			engine_render_sprites_in_sector_wrap(t_sector *sect, t_player *plr,
			t_sprt_r *d)
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

void		engine_render_sprites_in_sector(t_sector *sect, SDL_Surface *surf,
			t_player *plr, t_item_sprts *restr)
{
	t_sprt_r	d;

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
		engine_render_sprites_in_sector_3(sect, plr, &d);
		d.begx = max(d.x1, restr->sect_id.sx1);
		d.endx = min(d.x2, restr->sect_id.sx2);
		d.x = d.begx;
		while (d.x < d.endx)
		{
			d.cya = clamp(d.ya, restr->ytop[d.x], restr->ybottom[d.x]);
			d.cyb = clamp(d.yb, restr->ytop[d.x], restr->ybottom[d.x]);
			engine_render_sprites_in_sector_4(sect, surf, &d);
		}
		d.i++;
	}
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

void		get_sprite_rotatable_obj(t_player *plr,
			t_sprobject	*obj, t_sprt_r *d)
{
	t_point_2d	obj_dir;
	t_point_2d	plr_dir;
	float		angle;
	float		dot;
	float		det;

	obj_dir = (t_point_2d){plr->position.x - obj->position.x, plr->position.y - obj->position.y};
	plr_dir = (t_point_2d){-obj->position.x, -obj->position.y};
	dot = obj_dir.x * plr_dir.x + obj_dir.y * plr_dir.y;
	det = obj_dir.x * plr_dir.y - obj_dir.y * plr_dir.x;
	angle = atan2(det, dot);
	get_sprite_anim_obj(get_id_by_angle(angle * 180.0 / M_PI), plr, obj, d);
}

int			get_id_by_angle(float angle)
{
	if (angle >= 0 && angle <= 45)
		return (0);
	else if (angle > 45 && angle <= 90)
		return (1);
	else if (angle > 90 && angle <= 135)
		return (2);
	else if (angle > 135 && angle <= 180)
		return (3);
	else if (angle > -180 && angle <= -135)
		return (4);
	else if (angle > -135 && angle <= -90)
		return (5);
	else if (angle > -90 && angle <= -45)
		return (6);
	else
		return (7);
}

void		get_sprite_anim_obj(int angle_id,
			t_player *plr, t_sprobject *obj, t_sprt_r *d)
{
	d->img = obj->type->anmtn_360[obj->state][angle_id];
	if (((plr->anim % d->img->frames_delay) == 0)
	&& (obj->frame_num < d->img->frames_num))
		obj->frame_num++;
	if (obj->frame_num == d->img->frames_num)
		obj->frame_num = 0;
}

void		get_sprite_anim_obj_std(t_player *plr,
			t_sprobject *obj, t_sprt_r *d)
{
	d->img = obj->type->anmtn[obj->state];
	if (((plr->anim % d->img->frames_delay) == 0)
	&& (obj->frame_num < d->img->frames_num))
		obj->frame_num++;
	if (obj->frame_num == d->img->frames_num)
		obj->frame_num = 0;
}

float		magnitude_2d(t_point_2d *normal)
{
	return (sqrt((normal->x * normal->x) +
	(normal->y * normal->y)));
}

void		normalize_2d(t_point_2d *normal)
{
	float	magn;

	magn = magnitude_2d(normal);
	normal->x /= magn;
	normal->y /= magn;
}

float		dot_product_2d(t_point_2d a, t_point_2d b)
{
	float	res;

	res = 0;
	res += a.x * b.x;
	res += a.y * b.y;
	return (res);
}