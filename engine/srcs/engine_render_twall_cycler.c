/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_render_twall_cycler.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:06:28 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/16 17:46:01 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void				engine_render_twall_cycle(t_wall_clinks *l)
{

	t_color	color;

	color = l->eng->world->sectors_array[l->data->sect.sectorno].color;
	engine_vline_textured(l->surf, (t_scaler)scaler_init((float[5])
	{l->mdata->ya, l->mdata->cya, l->mdata->yb,
	0, l->data->polygone->tex_scale_koef}),
	(t_vline1_in){(t_fix_point_3d){l->cycler->x, l->mdata->cya, 0},
	(t_fix_point_3d){l->cycler->x,
	l->mdata->cyb, 0}, color, l->mdata->txtx}, l->data->polygone->texture);
}
