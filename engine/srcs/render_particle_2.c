/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_particle_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 21:09:00 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/24 19:25:38 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_render_particle_2(t_wallobj *particle, t_ptcl_r *data)
{
	if (data->t1.y <= 0 || data->t2.y <= 0)
	{
		data->nearz = 1e-4f;
		data->farz = 5;
		data->nearside = 1e-5f;
		data->farside = 60.f;
		data->i1 = intersect(data->t1, data->t2,
		(t_point_2d){-data->nearside, data->nearz},
		(t_point_2d){-data->farside, data->farz});
		data->i2 = intersect(data->t1, data->t2,
		(t_point_2d){data->nearside, data->nearz},
		(t_point_2d){data->farside, data->farz});
		data->org1 = data->t1;
		data->org2 = data->t2;
		engine_render_particle_3(data);
		engine_render_particle_4(particle, data);
	}
}

void		engine_render_particle_3(t_ptcl_r *data)
{
	if (data->t1.y < data->nearz)
	{
		if (data->i1.y > 0)
			data->t1 = data->i1;
		else
			data->t1 = data->i2;
	}
	if (data->t2.y < data->nearz)
	{
		if (data->i1.y > 0)
			data->t2 = data->i1;
		else
			data->t2 = data->i2;
	}
}

void		engine_render_particle_4(t_wallobj *particle, t_ptcl_r *data)
{
	if (fabsf(data->t2.x - data->t1.x)
	> fabsf(data->t2.y - data->t1.y))
	{
		data->u0 = (data->t1.x - data->org1.x)
		* (particle->texture->surface[particle->frame_num]->h - 1)
		/ (data->org2.x - data->org1.x);
		data->u1 = (data->t2.x - data->org1.x)
		* (particle->texture->surface[particle->frame_num]->h - 1)
		/ (data->org2.x - data->org1.x);
	}
	else
	{
		data->u0 = (data->t1.y - data->org1.y)
		* (particle->texture->surface[particle->frame_num]->w - 1)
		/ (data->org2.y - data->org1.y);
		data->u1 = (data->t2.y - data->org1.y)
		* (particle->texture->surface[particle->frame_num]->w - 1)
		/ (data->org2.y - data->org1.y);
	}
}

short		engine_render_particle_7(t_engine *eng, SDL_Surface *surf,
			t_wallobj *particle, t_ptcl_r *data)
{
	t_color	color;

	color = eng->world->sectors_array[data->sect.sectorno].color;
	data->ya = scaler_next(&data->ya_int);
	data->yb = scaler_next(&data->yb_int);
	if (data->ya == data->yb)
		return (0);
	data->cya = clamp(data->ya, eng->world->sectors_array
	[data->sect.sectorno].item_sprts.ytop[data->x],
	eng->world->sectors_array[data->sect.sectorno].item_sprts.ybottom[data->x]);
	data->cyb = clamp(data->yb, eng->world->sectors_array
	[data->sect.sectorno].item_sprts.ytop[data->x],
	eng->world->sectors_array[data->sect.sectorno].item_sprts.ybottom[data->x]);
	data->txtx = (data->u0 * ((data->x2 - data->x) * data->t2.y)
	+ data->u1 * ((data->x - data->x1) * data->t1.y))
	/ ((data->x2 - data->x) * data->t2.y + (data->x - data->x1) * data->t1.y);
	engine_vline_textured_surface(surf,
	(t_scaler)scaler_init((float[5]){data->ya, data->cya, data->yb,
	0, particle->texture->surface[particle->frame_num]->w - 1}),
	(t_vline1_in){(t_fix_point_3d){data->x, data->cya + 1, 0},
	(t_fix_point_3d){data->x, data->cyb, 0}, color,
	data->txtx}, particle->texture->surface[particle->frame_num]);
	data->x++;
	return (1);
}
