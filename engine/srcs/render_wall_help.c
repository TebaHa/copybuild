/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:58:58 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/18 18:38:04 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void			engine_render_wall_count_initial_point(t_object *object,
				t_player *plr, t_point_2d *t1, t_point_2d *t2)
{
	t_point_2d	v1;
	t_point_2d	v2;

	v1.x = object->vertices_array[0].x - plr->position.x;
	v1.y = object->vertices_array[0].y - plr->position.y;
	v2.x = object->vertices_array[1].x - plr->position.x;
	v2.y = object->vertices_array[1].y - plr->position.y;
	t1->x = v1.x * plr->sinangle - v1.y * plr->cosangle;
	t1->y = v1.x * plr->cosangle + v1.y * plr->sinangle;
	t2->x = v2.x * plr->sinangle - v2.y * plr->cosangle;
	t2->y = v2.x * plr->cosangle + v2.y * plr->sinangle;
}

void			engine_redner_wall_recount_prep_data(t_wall_help1 *data,
				t_point_2d *t1, t_point_2d *t2)
{
	data->nearz = 1e-4f;
	data->farz = 5;
	data->nearside = 1e-5f;
	data->farside = 60.f;
	data->i1 = intersect((t_point_2d){t1->x, t1->y}, (t_point_2d){t2->x, t2->y},
	(t_point_2d){-data->nearside, data->nearz},
	(t_point_2d){-data->farside, data->farz});
	data->i2 = intersect((t_point_2d){t1->x, t1->y},
	(t_point_2d){t2->x, t2->y},
	(t_point_2d){data->nearside, data->nearz},
	(t_point_2d){data->farside, data->farz});
	data->org1 = (t_point_2d){t1->x, t1->y};
	data->org2 = (t_point_2d){t2->x, t2->y};
}

void			engine_render_wall_recount_intersect_help(t_wall_help1 *data,
				t_point_2d *t1, t_point_2d *t2)
{
	if (t1->y < data->nearz)
	{
		if (data->i1.y > 0)
			*t1 = data->i1;
		else
			*t1 = data->i2;
	}
	if (t2->y < data->nearz)
	{
		if (data->i1.y > 0)
			*t2 = data->i1;
		else
			*t2 = data->i2;
	}
}

void			engine_render_wall_recount_intersect(t_polygone *polygone,
				t_point_2d *t1, t_point_2d *t2, int *u[2])
{
	t_wall_help1	data;

	engine_redner_wall_recount_prep_data(&data, t1, t2);
	engine_render_wall_recount_intersect_help(&data, t1, t2);
	if (fabsf(t2->x - t1->x) > fabsf(t2->y - t1->y))
	{
		*u[0] = (t1->x - data.org1.x) * (polygone->texture->height - 1)
		/ (data.org2.x - data.org1.x);
		*u[1] = (t2->x - data.org1.x) * (polygone->texture->height - 1)
		/ (data.org2.x - data.org1.x);
	}
	else
	{
		*u[0] = (t1->y - data.org1.y) * (polygone->texture->width - 1)
		/ (data.org2.y - data.org1.y);
		*u[1] = (t2->y - data.org1.y) * (polygone->texture->width - 1)
		/ (data.org2.y - data.org1.y);
	}
}
