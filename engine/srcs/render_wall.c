/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:19:23 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/14 23:59:10 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			*engine_render_wall_count_values(t_engine *eng,
		t_wall_help3 *data_help, t_wall_help2 *data, t_wall_mai_data *mdata)
{
	mdata->xscale1 = (WIDTH * hfov) / data_help->t1.y;
	mdata->yscale1 = (HEIGHT * vfov) / data_help->t1.y;
	mdata->x1 = WIDTH / 2 + (-data_help->t1.x * mdata->xscale1);
	mdata->xscale2 = (WIDTH * hfov) / data_help->t2.y;
	mdata->yscale2 = (HEIGHT * vfov) / data_help->t2.y;
	mdata->x2 = WIDTH / 2 + (-data_help->t2.x * mdata->xscale2);
	if(mdata->x1 >= mdata->x2 || mdata->x2 < data->sect.sx1 || mdata->x1 > data->sect.sx2)
		return (NULL);
	mdata->yceil =  eng->world->sectors_array[data->sect.sectorno].ceil - data->plr->position.z;
	mdata->yfloor = eng->world->sectors_array[data->sect.sectorno].floor - data->plr->position.z;
	mdata->nyceil = 0;
	mdata->nyfloor = 0;
	if(data->portal >= 0 && data->prev != data->portal)
	{
		mdata->nyceil  = eng->world->sectors_array[data->portal].ceil - data->plr->position.z;
		mdata->nyfloor = eng->world->sectors_array[data->portal].floor - data->plr->position.z;
		data_help->push = 1;
	}
	mdata->y1a = HEIGHT / 2 + (int)(-(mdata->yceil + data_help->t1.y * data->plr->yaw) * mdata->yscale1);
	mdata->y1b = HEIGHT / 2 + (int)(-(mdata->yfloor + data_help->t1.y * data->plr->yaw) * mdata->yscale1);
	mdata->y2a = HEIGHT / 2 + (int)(-(mdata->yceil + data_help->t2.y * data->plr->yaw) * mdata->yscale2);
	mdata->y2b = HEIGHT / 2 + (int)(-(mdata->yfloor + data_help->t2.y * data->plr->yaw) * mdata->yscale2);
	mdata->ny1a = HEIGHT / 2 + (int)(-(mdata->nyceil + data_help->t1.y * data->plr->yaw)  * mdata->yscale1);
	mdata->ny1b = HEIGHT / 2 + (int)(-(mdata->nyfloor + data_help->t1.y * data->plr->yaw) * mdata->yscale1);
	mdata->ny2a = HEIGHT / 2 + (int)(-(mdata->nyceil + data_help->t2.y * data->plr->yaw)  * mdata->yscale2);
	mdata->ny2b = HEIGHT / 2 + (int)(-(mdata->nyfloor + data_help->t2.y * data->plr->yaw) * mdata->yscale2);
	mdata->beginx = max(mdata->x1, data->sect.sx1);
	mdata->endx = min(mdata->x2, data->sect.sx2);
	mdata->ya_int = scaler_init((float [5]){mdata->x1, mdata->beginx, mdata->x2, mdata->y1a, mdata->y2a});
	mdata->yb_int = scaler_init((float [5]){mdata->x1, mdata->beginx, mdata->x2, mdata->y1b, mdata->y2b});
	mdata->nya_int = scaler_init((float [5]){mdata->x1, mdata->beginx, mdata->x2, mdata->ny1a, mdata->ny2a});
	mdata->nyb_int = scaler_init((float [5]){mdata->x1, mdata->beginx, mdata->x2, mdata->ny1b, mdata->ny2b});
	return (mdata);
}

void				engine_render_wall(t_engine *eng, SDL_Surface *surf, t_wall_help2 *data)
{
	t_wall_help3		data_help;
	t_wall_mai_data		mdata;
	t_wall_cycle		cycler;
	t_wall_clinks		links;

	data_help.push = 0;
	engine_render_wall_count_initial_point(data->polygone,
	data->plr, &data_help.t1, &data_help.t2);
	if(data_help.t1.y <= 0 && data_help.t2.y <= 0)
		return ;
	data_help.u0 = 0;
	data_help.u1 = data->polygone->texture->height - 1;
	if(data_help.t1.y <= 0 || data_help.t2.y <= 0)
		engine_render_wall_recount_intersect(data->polygone, &data_help.t1, &data_help.t2,
		(int *[2]){(int *)&data_help.u0, (int *)&data_help.u1});
	if (engine_render_wall_count_values(eng, &data_help, data, &mdata) == NULL)
		return ;
	cycler.x = mdata.beginx;
	links.cycler = &cycler;
	links.data = data;
	links.data_help = &data_help;
	links.eng = eng;
	links.mdata = &mdata;
	links.surf = surf;
	while (cycler.x <= mdata.endx)
	{
		engine_render_cycle_1(&links);
		engine_render_wall_cycle_3(&links);
		++cycler.x;
	}
	if (data_help.push)
		engine_render_wall_pusher(eng, data, &mdata);
	int		i = 0;
	while (eng->world->sectors_array[data->sect.sectorno].
	objects_array[data->obj_id].particles[i].id == 1 && i < 128)
	{
		engine_render_particles_wall(eng, surf, data, &mdata);
		i++;
	}
}

void				engine_render_wall_pusher(t_engine *eng,
					t_wall_help2 *data, t_wall_mai_data *mdata)
{
	engine_push_renderstack(eng->world->renderstack,
	(t_item){data->portal, mdata->beginx, mdata->endx});
	eng->world->sectors_array[data->portal].item_sprts.sect_id = (t_item)
	{data->portal, mdata->beginx, mdata->endx};
	one_dim_zbuffers_copy(&eng->world->sectors_array[data->portal].item_sprts,
	data->ytop, data->ybottom);
	engine_push_spriterenderstack(eng->world->sprite_renderstack,
	&eng->world->sectors_array[data->portal].item_sprts);
}

void				engine_render_particles_wall(t_engine *eng, SDL_Surface *surf,
					t_wall_help2 *data, t_wall_mai_data *mdata)
{
	int		i = 0;

	while (eng->world->sectors_array[data->sect.sectorno].
	objects_array[data->obj_id].particles[i].id == 1 && i < 128)
	{
		if (eng->world->sectors_array[data->sect.sectorno].
		objects_array[data->obj_id].particles[i].z
		> eng->world->sectors_array[data->sect.sectorno].floor &&
		eng->world->sectors_array[data->sect.sectorno].
		objects_array[data->obj_id].particles[i].z
		< eng->world->sectors_array[data->sect.sectorno].ceil)
			engine_render_particle(eng, surf,
			&eng->world->sectors_array[data->sect.sectorno].
			objects_array[data->obj_id].particles[i],
			&eng->world->sectors_array[data->sect.sectorno].
			objects_array[data->obj_id], data->plr, data->sect);
		i++;
	}
}