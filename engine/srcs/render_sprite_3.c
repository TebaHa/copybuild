/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_render_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 14:52:11 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 14:53:02 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		get_sprite_anim_obj(int angle_id,
			t_player *plr, t_sprobject *obj, t_sprt_r *d)
{
	d->img = obj->type->anmtn_360[obj->state][angle_id];
	if (d->img->a_state == CYCLE || obj->state == E_IDLE)
	{
		if (((plr->anim % (d->img->frames_delay * 2)) == 0)
		&& (obj->frame_num < d->img->frames_num))
			obj->frame_num++;
		if (obj->frame_num == d->img->frames_num)
			obj->frame_num = 0;
	}
	else if (d->img->a_state == ANIMATE)
	{
		if (((plr->anim % (d->img->frames_delay * 2)) == 0)
		&& (obj->frame_num < d->img->frames_num))
			obj->frame_num++;
		if (obj->frame_num == d->img->frames_num - 1)
			obj->norender = true;
	}
}

void		get_sprite_anim_obj_std(t_player *plr,
			t_sprobject *obj, t_sprt_r *d)
{
	d->img = obj->type->anmtn[obj->state];
	if (d->img->a_state == CYCLE || obj->state == E_IDLE)
	{
		if (((plr->anim % (d->img->frames_delay * 2)) == 0)
		&& (obj->frame_num < d->img->frames_num))
			obj->frame_num++;
		if (obj->frame_num == d->img->frames_num)
			obj->frame_num = 0;
	}
	else if (d->img->a_state == ANIMATE)
	{
		if (((plr->anim % (d->img->frames_delay * 2)) == 0)
		&& (obj->frame_num < d->img->frames_num))
			obj->frame_num++;
		if (obj->frame_num == d->img->frames_num - 1)
			obj->norender = true;
	}
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
