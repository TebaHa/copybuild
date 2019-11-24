/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cycle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:39:27 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/24 14:19:04 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int					engine_render_cycle_5(t_wall_clinks *l)
{
	t_color	color;

	color = l->eng->world->sectors_array[l->data->sect.sectorno].color;
	l->cycler->tex = l->cycler->y < l->mdata->cya
	? l->eng->world->sectors_array[l->data->sect.sectorno].ceil_texture
	: l->eng->world->sectors_array[l->data->sect.sectorno].floor_texture;
	if (l->cycler->tex == NULL)
		return (0);
	l->cycler->txtx = (l->cycler->pnts.x) * 0.5;
	l->cycler->txtz = (l->cycler->pnts.z) * 0.5;
	l->cycler->offset = (((l->cycler->txtz %
	l->cycler->tex->height) * l->cycler->tex->width)
	+ (l->cycler->txtx % l->cycler->tex->width)) * l->cycler->tex->channels;
	l->cycler->red = (l->cycler->tex->data)[l->cycler->offset] * color.red;
	l->cycler->green = (l->cycler->tex->data)[l->cycler->offset + 1]
	* color.green;
	l->cycler->blue = (l->cycler->tex->data)[l->cycler->offset + 2]
	* color.blue;
	return (1);
}

void				engine_render_cycle_2(t_wall_clinks *l)
{
	l->cycler->y = l->data->ytop[l->cycler->x];
	while (l->cycler->y <= l->data->ybottom[l->cycler->x])
	{
		if (l->cycler->y >= l->mdata->cya && l->cycler->y <= l->mdata->cyb)
		{
			l->cycler->y = l->mdata->cyb;
			(l->cycler->y) += 1;
			continue;
		}
		l->cycler->hei = l->cycler->y < l->mdata->cya
		? l->mdata->yceil : l->mdata->yfloor;
		l->cycler->pnts = relative_map_coordinate_to_absolute(l->data->plr,
		l->cycler->hei, l->cycler->x, l->cycler->y);
		if (engine_render_cycle_5(l) == 0)
		{
			(l->cycler->y) += 1;
			continue;
		}
		((int*)l->surf->pixels)
		[l->cycler->y * WIDTH + l->cycler->x] = get_rgb((int)l->cycler->red,
		(int)l->cycler->green, (int)l->cycler->blue, 255);
		(l->cycler->y) += 1;
	}
}

void				engine_render_cycle_1(t_wall_clinks *l)
{
	l->mdata->ya = scaler_next(&l->mdata->ya_int);
	l->mdata->yb = scaler_next(&l->mdata->yb_int);
	l->mdata->cya = clamp(l->mdata->ya, l->data->ytop[l->cycler->x],
	l->data->ybottom[l->cycler->x]);
	l->mdata->cyb = clamp(l->mdata->yb, l->data->ytop[l->cycler->x],
	l->data->ybottom[l->cycler->x]);
	l->mdata->txtx = (l->data_help->u0 * ((l->mdata->x2 - l->cycler->x)
	* l->data_help->t2.y) + l->data_help->u1
	* ((l->cycler->x - l->mdata->x1) * l->data_help->t1.y))
	/ ((l->mdata->x2 - l->cycler->x) * l->data_help->t2.y + (l->cycler->x
	- l->mdata->x1) * l->data_help->t1.y);
	engine_render_cycle_2(l);
}

void				engine_render_wall_cycle_4(t_wall_clinks *l)
{
	t_color	color;

	color = l->eng->world->sectors_array[l->data->sect.sectorno].color;
	l->mdata->nya = scaler_next(&l->mdata->nya_int);
	l->mdata->nyb = scaler_next(&l->mdata->nyb_int);
	l->mdata->cnya = clamp(l->mdata->nya, l->data->ytop[l->cycler->x],
	l->data->ybottom[l->cycler->x]);
	l->mdata->cnyb = clamp(l->mdata->nyb,
	l->data->ytop[l->cycler->x], l->data->ybottom[l->cycler->x]);
	engine_vline_textured(l->surf, (t_scaler)scaler_init((float[5])
	{l->mdata->ya, l->mdata->cya, l->mdata->yb,
	0, l->eng->world->sectors_array[l->data->sect.sectorno]
	.objects_array[l->data->obj_id].ceil_wall_texture->height - 1}),
	(t_vline1_in){(t_fix_point_3d){l->cycler->x, l->mdata->cya, 0},
	(t_fix_point_3d){l->cycler->x,
	l->mdata->cnya + 1, 0}, color, l->mdata->txtx},
	l->eng->world->sectors_array[l->data->sect.sectorno]
	.objects_array[l->data->obj_id].ceil_wall_texture);
	l->data->ytop[l->cycler->x] = clamp(max(l->mdata->cya, l->mdata->cnya),
	l->data->ytop[l->cycler->x], HEIGHT - 1);
	engine_render_wall_cycle_6(l);
}

void				engine_render_wall_cycle_3(t_wall_clinks *l)
{
	t_color	color;

	color = l->eng->world->sectors_array[l->data->sect.sectorno].color;
	if (l->data->portal >= 0)
	{
		engine_render_wall_cycle_4(l);
	}
	else
	{
		engine_vline_textured(l->surf, (t_scaler)scaler_init((float[5])
		{l->mdata->ya, l->mdata->cya, l->mdata->yb,
		0, l->data->polygone->tex_scale_koef}),
		(t_vline1_in){(t_fix_point_3d){l->cycler->x, l->mdata->cya, 0},
		(t_fix_point_3d){l->cycler->x,
		l->mdata->cyb + 1, 0}, color, l->mdata->txtx},
		l->data->polygone->texture);
	}
}
