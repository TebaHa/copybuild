/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 19:19:23 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/14 21:41:33 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

/*
**	Wall render funs
**
*/

void		engine_render_wall_count_initial_point(t_polygone *polygone, t_player *plr, t_point_2d	*t1, t_point_2d	*t2)
{
	t_point_2d	v1;
	t_point_2d	v2;

	v1.x = polygone->vertices_array[0].x - plr->position.x;
	v1.y = polygone->vertices_array[0].y - plr->position.y;
	v2.x = polygone->vertices_array[1].x - plr->position.x;
	v2.y = polygone->vertices_array[1].y - plr->position.y;
	t1->x = v1.x * plr->sinangle - v1.y * plr->cosangle;
	t1->y = v1.x * plr->cosangle + v1.y * plr->sinangle;
	t2->x = v2.x * plr->sinangle - v2.y * plr->cosangle;
	t2->y = v2.x * plr->cosangle + v2.y * plr->sinangle;
}

void		engine_redner_wall_recount_prep_data(t_wall_help1 *data,
			t_point_2d *t1, t_point_2d *t2)
{
	data->nearz = 1e-4f;
	data->farz = 5;
	data->nearside = 1e-5f;
	data->farside = 60.f;
	data->i1 = intersect((t_point_2d){t1->x, t1->y}, (t_point_2d){t2->x, t2->y},
	(t_point_2d){-data->nearside, data->nearz}, (t_point_2d){-data->farside, data->farz});
	data->i2 = intersect((t_point_2d){t1->x, t1->y}, (t_point_2d){t2->x, t2->y},
	(t_point_2d){data->nearside, data->nearz}, (t_point_2d){data->farside, data->farz});
	data->org1 = (t_point_2d){t1->x, t1->y};
	data->org2 = (t_point_2d){t2->x, t2->y};
}

void		engine_render_wall_recount_intersect_help(t_wall_help1 *data,
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

void		engine_render_wall_recount_intersect(t_polygone *polygone,
			t_point_2d *t1, t_point_2d *t2, int *u[2])
{
	t_wall_help1	data;

	engine_redner_wall_recount_prep_data(&data, t1, t2);
	engine_render_wall_recount_intersect_help(&data, t1, t2);
	if(fabsf(t2->x - t1->x) > fabsf(t2->y - t1->y))
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

/*
void		engine_render_wall_count_values(t_point_2d t1[2], t_engine *eng, t_player *plr, t_item *sect)
{
	float	xscale1 = (WIDTH * hfov) / t1->y;
	float	yscale1 = (HEIGHT * vfov) / t1->y;
	int x1 = WIDTH / 2 + (-t1->x * xscale1);
	float xscale2 = (WIDTH * hfov) / t2->y, yscale2 = (HEIGHT * vfov) / t2->y;
	int x2 = WIDTH / 2 + (-t2->x * xscale2);
	if(x1 >= x2 || x2 < sect->sx1 || x1 > sect->sx2)
		return;
	float yceil =  eng->world->sectors_array[sect->sectorno].ceil - plr->position.z;
	float yfloor = eng->world->sectors_array[sect->sectorno].floor - plr->position.z;
	float nyceil = 0, nyfloor = 0;
	if(portal >= 0 && prev != portal)
	{
		nyceil  = eng->world->sectors_array[portal].ceil - plr->position.z;
		nyfloor = eng->world->sectors_array[portal].floor - plr->position.z;
		push = 1;
	}
	int y1a  = HEIGHT / 2 + (int)(-(yceil + t1->y * plr->yaw) * yscale1), y1b = HEIGHT / 2 + (int)(-(yfloor + t1->y * plr->yaw)  * yscale1);
	int y2a  = HEIGHT / 2 + (int)(-(yceil + t2->y * plr->yaw)  * yscale2), y2b = HEIGHT / 2 + (int)(-(yfloor + t2->y * plr->yaw)  * yscale2);
	int ny1a = HEIGHT / 2 + (int)(-(nyceil + t1->y * plr->yaw)  * yscale1), ny1b = HEIGHT / 2 + (int)(-(nyfloor + t1->y * plr->yaw) * yscale1);
	int ny2a = HEIGHT / 2 + (int)(-(nyceil + t2->y * plr->yaw)  * yscale2), ny2b = HEIGHT / 2 + (int)(-(nyfloor + t2->y * plr->yaw) * yscale2);
	int beginx = max(x1, sect->sx1), endx = min(x2, sect->sx2);
	unsigned r;Z
	t_scaler ya_int = scaler_init((float [5]){x1, beginx, x2, y1a, y2a});
	t_scaler yb_int = scaler_init((float [5]){x1, beginx, x2, y1b, y2b});
	t_scaler nya_int = scaler_init((float [5]){x1, beginx, x2, ny1a, ny2a});
	t_scaler nyb_int = scaler_init((float [5]){x1, beginx, x2, ny1b, ny2b});
}
*/
void		engine_render_wall(t_engine *eng, SDL_Surface *surf, t_wall_help2 *data)
{
	t_point_2d	t1;
	t_point_2d	t2;
	int			push;
	int			u0;
	int			u1;

	push = 0;
	engine_render_wall_count_initial_point(data->polygone, data->plr, &t1, &t2);
	if(t1.y <= 0 && t2.y <= 0)
		return ;
	u0 = 0;
	u1 = data->polygone->texture->height - 1;
	if(t1.y <= 0 || t2.y <= 0)
		engine_render_wall_recount_intersect(data->polygone, &t1, &t2, (int *[2]){(int *)&u0, (int *)&u1});
	float xscale1 = (WIDTH * hfov) / t1.y, yscale1 = (HEIGHT * vfov) / t1.y;
	int x1 = WIDTH / 2 + (-t1.x * xscale1);
	float xscale2 = (WIDTH * hfov) / t2.y, yscale2 = (HEIGHT * vfov) / t2.y;
	int x2 = WIDTH / 2 + (-t2.x * xscale2);
	if(x1 >= x2 || x2 < data->sect.sx1 || x1 > data->sect.sx2)
		return;
	float yceil =  eng->world->sectors_array[data->sect.sectorno].ceil - data->plr->position.z;
	float yfloor = eng->world->sectors_array[data->sect.sectorno].floor - data->plr->position.z;
	float nyceil = 0, nyfloor = 0;
	if(data->portal >= 0 && data->prev != data->portal)
	{
		nyceil  = eng->world->sectors_array[data->portal].ceil - data->plr->position.z;
		nyfloor = eng->world->sectors_array[data->portal].floor - data->plr->position.z;
		push = 1;
	}
	int y1a = HEIGHT / 2 + (int)(-(yceil + t1.y * data->plr->yaw) * yscale1);
	int y1b = HEIGHT / 2 + (int)(-(yfloor + t1.y * data->plr->yaw)  * yscale1);
	int y2a = HEIGHT / 2 + (int)(-(yceil + t2.y * data->plr->yaw)  * yscale2);
	int y2b = HEIGHT / 2 + (int)(-(yfloor + t2.y * data->plr->yaw)  * yscale2);
	int ny1a = HEIGHT / 2 + (int)(-(nyceil + t1.y * data->plr->yaw)  * yscale1);
	int ny1b = HEIGHT / 2 + (int)(-(nyfloor + t1.y * data->plr->yaw) * yscale1);
	int ny2a = HEIGHT / 2 + (int)(-(nyceil + t2.y * data->plr->yaw)  * yscale2);
	int ny2b = HEIGHT / 2 + (int)(-(nyfloor + t2.y * data->plr->yaw) * yscale2);
	int beginx = max(x1, data->sect.sx1), endx = min(x2, data->sect.sx2);
	unsigned r;
	t_scaler ya_int = scaler_init((float [5]){x1, beginx, x2, y1a, y2a});
	t_scaler yb_int = scaler_init((float [5]){x1, beginx, x2, y1b, y2b});
	t_scaler nya_int = scaler_init((float [5]){x1, beginx, x2, ny1a, ny2a});
	t_scaler nyb_int = scaler_init((float [5]){x1, beginx, x2, ny1b, ny2b});
	for(int x = beginx; x <= endx; ++x)
	{
		int ya = scaler_next(&ya_int);
		int yb = scaler_next(&yb_int);
		int cya = clamp(ya, data->ytop[x], data->ybottom[x]);
		int cyb = clamp(yb, data->ytop[x], data->ybottom[x]);
		int txtx = (u0 * ((x2 - x) * t2.y) + u1 * ((x - x1) * t1.y)) / ((x2-x) * t2.y + (x - x1) * t1.y);
		t_image *tex = NULL;
		for(int y = data->ytop[x]; y <= data->ybottom[x]; ++y)
		{
			if(y >= cya && y <= cyb)
			{
				y = cyb;
				continue;
			}
			float hei = y < cya ? yceil : yfloor;
			t_costil pnts = relative_map_coordinate_to_absolute(data->plr, hei, x, y);
			tex = y < cya ? eng->world->sectors_array[data->sect.sectorno].ceil_texture : eng->world->sectors_array[data->sect.sectorno].floor_texture;
			unsigned txtx = (pnts.x), txtz = (pnts.z);
			int offset = (((txtz % tex->height) * tex->width) + (txtx % tex->width)) * tex->channels;
			int8_t red = (tex->data)[offset];
			int8_t green = (tex->data)[offset + 1];
			int8_t blue = (tex->data)[offset + 2];
			int color = get_rgb((int)red, (int)green, (int)blue, 255);
			((int*)surf->pixels)[y * WIDTH + x] = color;
		}
		if (data->portal >= 0)
		{
			int nya = scaler_next(&nya_int);
			int nyb = scaler_next(&nyb_int);
			int cnya = clamp(nya, data->ytop[x], data->ybottom[x]);
			int cnyb = clamp(nyb, data->ytop[x], data->ybottom[x]);
			engine_vline_textured(surf, (t_scaler)scaler_init((float [5]){ya, cya, yb, 0, data->polygone->texture->height - 1}),
			(t_fix_point_3d){x, cya, 0}, (t_fix_point_3d){x, cnya-1, 0}, txtx, eng->world->sectors_array[data->sect.sectorno].objects_array[data->obj_id].floor_wall_texture);
			data->ytop[x] = clamp(max(cya, cnya), data->ytop[x], HEIGHT - 1);
			engine_vline_textured(surf, (t_scaler)scaler_init((float [5]){ya, cnyb + 1, yb, 0, data->polygone->texture->height - 1}),
			(t_fix_point_3d){x, cnyb + 1, 0}, (t_fix_point_3d){x, cyb, 0}, txtx, eng->world->sectors_array[data->sect.sectorno].objects_array[data->obj_id].floor_wall_texture);
			data->ybottom[x] = clamp(min(cyb, cnyb), 0, data->ybottom[x]);
		}
		else
			engine_vline_textured(surf, (t_scaler)scaler_init((float [5]){ya, cya, yb, 0, data->polygone->texture->height - 1}),
			(t_fix_point_3d){x, cya + 1, 0}, (t_fix_point_3d){x, cyb, 0}, txtx, data->polygone->texture);
	}
	if (push)
	{
		engine_push_renderstack(eng->world->renderstack, (t_item){data->portal, beginx, endx});
		eng->world->sectors_array[data->portal].item_sprts.sect_id = (t_item){data->portal, beginx, endx};
		one_dim_zbuffers_copy(&eng->world->sectors_array[data->portal].item_sprts, data->ytop, data->ybottom);
		engine_push_spriterenderstack(eng->world->sprite_renderstack, &eng->world->sectors_array[data->portal].item_sprts);
	}
	int		i = 0;
	while (eng->world->sectors_array[data->sect.sectorno].objects_array[data->obj_id].particles[i].id == 1 && i < 128)
	{
		if (eng->world->sectors_array[data->sect.sectorno].objects_array[data->obj_id].particles[i].z > eng->world->sectors_array[data->sect.sectorno].floor &&
		eng->world->sectors_array[data->sect.sectorno].objects_array[data->obj_id].particles[i].z < eng->world->sectors_array[data->sect.sectorno].ceil)
			engine_render_particle(eng, surf, &eng->world->sectors_array[data->sect.sectorno].objects_array[data->obj_id].particles[i],
					&eng->world->sectors_array[data->sect.sectorno].objects_array[data->obj_id], data->plr, data->sect);
		i++;
	}
}
