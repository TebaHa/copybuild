/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_cycle2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:43:44 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/18 20:26:49 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_render_wall_cycle_6(t_wall_clinks *l)
{
	engine_vline_textured(l->surf,
	(t_scaler)scaler_init((float[5]){l->mdata->ya,
	l->mdata->cnyb + 1,
	l->mdata->yb, 0, l->data->polygone->texture->height - 1}),
	(t_vline1_in){(t_fix_point_3d){l->cycler->x, l->mdata->cnyb + 1, 0},
	(t_fix_point_3d){l->cycler->x, l->mdata->cyb, 0},
	l->mdata->txtx}, l->eng->world->sectors_array[l->data->sect.sectorno]
	.objects_array[l->data->obj_id].floor_wall_texture);
	l->data->ybottom[l->cycler->x] = clamp(min(l->mdata->cyb,
	l->mdata->cnyb), 0, l->data->ybottom[l->cycler->x]);
}
