/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_render_twall_cycler.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:06:28 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/18 19:13:18 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void				engine_render_twall_cycle(t_wall_clinks *l)
{
	engine_vline_textured(l->surf, (t_scaler)scaler_init((float[5])
	{l->mdata->ya, l->mdata->cya, l->mdata->yb,
	0, l->data->polygone->tex_scale_koef}),
	(t_vline1_in){(t_fix_point_3d){l->cycler->x, l->mdata->cya, 0},
	(t_fix_point_3d){l->cycler->x,
	l->mdata->cyb, 0}, l->data->color, l->mdata->txtx}, l->data->polygone->texture);
}
