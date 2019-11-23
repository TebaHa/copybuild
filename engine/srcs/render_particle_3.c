/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_particle_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:32:03 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 15:34:40 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

short	engine_render_particle_6(t_wallobj *particle, t_ptcl_r *data)
{
	data->yceil = (particle->z + particle->texture->surface
	[particle->frame_num]->h / 4)
	- data->plr->position.z;
	data->yfloor = (particle->z - particle->texture->surface
	[particle->frame_num]->h / 4)
	- data->plr->position.z;
	if (data->yceil <= data->yfloor)
		return (0);
	data->y1a = HEIGHT / 2 + (int)(-(data->yceil
	+ data->t1.y * data->plr->yaw)
	* data->yscale1);
	data->y1b = HEIGHT / 2 + (int)(-(data->yfloor
	+ data->t1.y * data->plr->yaw)
	* data->yscale1);
	data->y2a = HEIGHT / 2 + (int)(-(data->yceil
	+ data->t2.y * data->plr->yaw)
	* data->yscale2);
	data->y2b = HEIGHT / 2 + (int)(-(data->yfloor
	+ data->t2.y * data->plr->yaw)
	* data->yscale2);
	engine_render_particle_8(particle, data);
	return (1);
}

void	engine_render_particle_8(t_wallobj *particle, t_ptcl_r *data)
{
	data->beginx = max(data->x1, data->sect.sx1);
	data->endx = min(data->x2, data->sect.sx2);
	data->ya_int = scaler_init((float[5]){data->x1, data->beginx,
	data->x2, data->y1a, data->y2a});
	data->yb_int = scaler_init((float[5]){data->x1, data->beginx,
	data->x2, data->y1b, data->y2b});
	data->x = data->beginx;
}
