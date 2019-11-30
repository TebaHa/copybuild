/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cycle2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:43:44 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/26 19:34:26 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_render_wall_cycle_6(t_wall_clinks *l)
{
	t_color	color;

	color = l->eng->world->sectors_array[l->data->sect.sectorno].color;
	engine_vline_textured(l->surf,
	(t_scaler)scaler_init((float[5]){l->mdata->ya,
	l->mdata->cnyb,
	l->mdata->yb, 0, l->eng->world->sectors_array[l->data->sect.sectorno]
	.objects_array[l->data->obj_id].floor_wall_texture->height - 1}),
	(t_vline1_in){(t_fix_point_3d){l->cycler->x, ceilf(l->mdata->cnyb), 0},
	(t_fix_point_3d){l->cycler->x, ceilf(l->mdata->cyb - 1), 0}, color,
	l->mdata->txtx}, l->eng->world->sectors_array[l->data->sect.sectorno]
	.objects_array[l->data->obj_id].floor_wall_texture);
	l->data->ybottom[l->cycler->x] = clamp(min(l->mdata->cyb,
	l->mdata->cnyb), 0, l->data->ybottom[l->cycler->x]) + 1;
}

void		engine_render_wall_cycle_main_wall(t_wall_clinks *l)
{
	t_color	color;
	t_image	*img;

	color = l->eng->world->sectors_array[l->data->sect.sectorno].color;
	if (l->data->polygone->texture)
		img = l->data->polygone->texture;
	else if (l->eng->world->sectors_array[l->data->sect.sectorno]
	.objects_array[l->data->obj_id].ceil_wall_texture)
		img = l->eng->world->sectors_array[l->data->sect.sectorno]
		.objects_array[l->data->obj_id].ceil_wall_texture;
	else if (l->eng->world->sectors_array[l->data->sect.sectorno]
	.objects_array[l->data->obj_id].floor_wall_texture)
		img = l->eng->world->sectors_array[l->data->sect.sectorno]
		.objects_array[l->data->obj_id].floor_wall_texture;
	else
		return;
	engine_vline_textured(l->surf, (t_scaler)scaler_init((float[5])
	{l->mdata->ya, l->mdata->cya, l->mdata->yb,
	0, l->data->polygone->tex_scale_koef}),
	(t_vline1_in){(t_fix_point_3d){l->cycler->x, ceilf(l->mdata->cya), 0},
	(t_fix_point_3d){l->cycler->x,
	ceilf(l->mdata->cyb), 0}, color, l->mdata->txtx}, img);
}
