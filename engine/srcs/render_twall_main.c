/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_render_twall_main.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:58:34 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/24 17:19:17 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			*engine_render_twall_count_values(t_engine *eng,
	t_wall_help3 *data_help, t_wall_help2 *data, t_wall_mai_data *mdata)
{
	mdata->xscale1 = (WIDTH * HFOV) / data_help->t1.y;
	mdata->yscale1 = (HEIGHT * VFOV) / data_help->t1.y;
	mdata->x1 = WIDTH / 2 + (-data_help->t1.x * mdata->xscale1);
	mdata->xscale2 = (WIDTH * HFOV) / data_help->t2.y;
	mdata->yscale2 = (HEIGHT * VFOV) / data_help->t2.y;
	mdata->x2 = WIDTH / 2 + (-data_help->t2.x * mdata->xscale2);
	if (mdata->x1 >= mdata->x2 || mdata->x2 <
	0 || mdata->x1 > WIDTH - 1)
		return (NULL);
	mdata->yceil = eng->world->sectors_array[data->sect.sectorno].
	ceil - data->plr->position.z;
	mdata->yfloor = eng->world->sectors_array[data->sect.sectorno].
	floor - data->plr->position.z;
	engine_render_twall_c_val2(data_help, data, mdata);
	return (mdata);
}

void			engine_render_twall_c_val2(t_wall_help3 *data_help,
				t_wall_help2 *data, t_wall_mai_data *mdata)
{
	mdata->y1a = HEIGHT / 2 + (int)(-(mdata->yceil
	+ data_help->t1.y * data->plr->yaw) * mdata->yscale1);
	mdata->y1b = HEIGHT / 2 + (int)(-(mdata->yfloor
	+ data_help->t1.y * data->plr->yaw) * mdata->yscale1);
	mdata->y2a = HEIGHT / 2 + (int)(-(mdata->yceil
	+ data_help->t2.y * data->plr->yaw) * mdata->yscale2);
	mdata->y2b = HEIGHT / 2 + (int)(-(mdata->yfloor
	+ data_help->t2.y * data->plr->yaw) * mdata->yscale2);
	engine_render_twall_c_val3(data, mdata);
}

void			engine_render_twall_c_val3(t_wall_help2 *data,
				t_wall_mai_data *mdata)
{
	mdata->beginx = max(mdata->x1, data->sect.sx1);
	mdata->endx = min(mdata->x2, data->sect.sx2);
	mdata->ya_int = scaler_init((float[5]){mdata->x1,
	mdata->beginx, mdata->x2, mdata->y1a, mdata->y2a});
	mdata->yb_int = scaler_init((float[5]){mdata->x1,
	mdata->beginx, mdata->x2, mdata->y1b, mdata->y2b});
}

void			engine_render_twall(t_engine *eng, SDL_Surface *surf,
				t_wall_help2 *data, t_render_stacks *stacks)
{
	t_wall_help3		data_help;
	t_wall_mai_data		mdata;
	t_wall_cycle		cycler;
	t_wall_clinks		links;

	data_help.push = 0;
	engine_render_twall_count_initial_point(data->polygone,
	data->plr, &data_help.t1, &data_help.t2);
	if (data_help.t1.y <= 0 && data_help.t2.y <= 0)
		return ;
	data_help.u0 = 0;
	data_help.u1 = data->polygone->tex_scale_koef;
	if (data_help.t1.y <= 0 || data_help.t2.y <= 0)
		engine_render_twall_recount_intersect(data->polygone,
		&data_help.t1, &data_help.t2,
		(int *[2]){(int *)&data_help.u0, (int *)&data_help.u1});
	if (engine_render_twall_count_values(eng, &data_help, data, &mdata) == NULL)
		return ;
	cycler.x = mdata.beginx;
	engine_set_tlinks(&links, (void *[6]){&cycler, data, &data_help,
	eng, &mdata, surf});
	engine_render_twall_main_cycler(&links, &cycler, &mdata);
}
