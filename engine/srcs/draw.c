/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:42:08 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/21 22:04:21 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int			get_rgb(int r, int g, int b, int a)
{
	return (((((int)r) << 24) & 0xFF000000) | ((((int)g) << 16) & 0x00FF0000) | (((b) << 8) & 0x0000FF00) | (((a)) & 0x000000FF));
}

void		engine_render_world(t_engine *eng, t_player plr, SDL_Surface *surf)
{
	int			ytop[WIDTH] = {0};
	int			ybottom[WIDTH];
	unsigned	x;
	t_item		sect_id;
	int			prev;
	int			i;
	int			j;

	x = 0;
	prev = -1;
	SDL_LockSurface(surf);
	while (x < WIDTH)
		ybottom[x++] = HEIGHT;
	sect_id = (t_item){plr.cursector, 0, WIDTH - 1};
	engine_push_renderstack(eng->world->renderqueue, sect_id);
	while (((sect_id = engine_pop_renderstack(eng->world->renderqueue)).sectorno >= 0))
	{
		i = 0;
		while (i < eng->world->sectors_array[sect_id.sectorno].objects_count)
		{
			engine_render_wall(eng, surf, eng->world->sectors_array[sect_id.sectorno].objects_array[i].polies_array, &plr,
				ytop, ybottom, eng->world->sectors_array[sect_id.sectorno].objects_array[i].portal, NULL, sect_id, i, prev);
			i++;
		}
		prev = sect_id.sectorno;
	}
	engine_clear_renderstack(eng->world->renderqueue);
	SDL_UnlockSurface(surf);
}

void		engine_render_wall(t_engine *eng, SDL_Surface *surf, t_polygone *polygone, t_player *plr, int *ytop, int *ybottom, int portal, int *rendered, t_item sect, int obj_id, int prev)
{
	t_point_2d	v1;
	t_point_2d	v2;
	t_point_2d	t1;
	t_point_2d	t2;
	t_line		renderbox;
	int			push;

	push = 0;
	v1.x = polygone->vertices_array[0].x - plr->position.x;
	v1.y = polygone->vertices_array[0].y - plr->position.y;
	v2.x = polygone->vertices_array[1].x - plr->position.x;
	v2.y = polygone->vertices_array[1].y - plr->position.y;
	/* Rotate them around the player's view */
	t1.x = v1.x * plr->sinangle - v1.y * plr->cosangle;
	t1.y = v1.x * plr->cosangle + v1.y * plr->sinangle;
	t2.x = v2.x * plr->sinangle - v2.y * plr->cosangle;
	t2.y = v2.x * plr->cosangle + v2.y * plr->sinangle;
	/* Is the wall at least partially in front of the player? */
	if(t1.y <= 0 && t2.y <= 0)
		return ;
	int u0 = 0, u1 = polygone->texture->height - 1;
	/* If it's partially behind the player, clip it against player's view frustrum */
	if(t1.y <= 0 || t2.y <= 0)
	{
		float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 60.f;
		// Find an intersection between the wall and the approximate edges of player's view
		t_point_2d i1 = Intersect(t1.x, t1.y, t2.x, t2.y, -nearside, nearz, -farside, farz);
		t_point_2d i2 = Intersect(t1.x, t1.y, t2.x, t2.y, nearside, nearz, farside, farz);
		t_point_2d org1 = {t1.x, t1.y}, org2 = {t2.x, t2.y};
		if(t1.y < nearz)
		{
			if(i1.y > 0)
				t1 = i1;
			else
				t1 = i2;
		}
		if(t2.y < nearz)
		{
			if(i1.y > 0)
				t2 = i1;
			else
				t2 = i2;
		}
		if(fabsf(t2.x - t1.x) > fabsf(t2.y - t1.y))
			u0 = (t1.x - org1.x) * (polygone->texture->height - 1) / (org2.x-org1.x), u1 = (t2.x - org1.x) * (polygone->texture->height - 1) / (org2.x - org1.x);
		else
			u0 = (t1.y - org1.y) * (polygone->texture->width - 1) / (org2.y-org1.y), u1 = (t2.y - org1.y) * (polygone->texture->width - 1) / (org2.y - org1.y);
	}
	/* Do perspective transformation */
	float xscale1 = (WIDTH * hfov) / t1.y, yscale1 = (HEIGHT * vfov) / t1.y;
	int x1 = WIDTH / 2 + (-t1.x * xscale1);
	float xscale2 = (WIDTH * hfov) / t2.y, yscale2 = (HEIGHT * vfov) / t2.y;
	int x2 = WIDTH / 2 + (-t2.x * xscale2);
	if(x1 >= x2 || x2 < sect.sx1 || x1 > sect.sx2)
		return; // Only render if it's visible
	/* Acquire the floor and ceiling heights, relative to where the player's view is */
	float yceil =  eng->world->sectors_array[sect.sectorno].ceil - plr->position.z;
	float yfloor = eng->world->sectors_array[sect.sectorno].floor - plr->position.z;
	/* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
	float nyceil = 0, nyfloor = 0;
	if(portal >= 0 && prev != portal) // Is another sector showing through this portal?
	{
		nyceil  = eng->world->sectors_array[portal].ceil - plr->position.z;
		nyfloor = eng->world->sectors_array[portal].floor - plr->position.z;
		push = 1;
	}
	int y1a  = HEIGHT / 2 + (int)(-(yceil + t1.y * plr->yaw) * yscale1), y1b = HEIGHT / 2 + (int)(-(yfloor + t1.y * plr->yaw)  * yscale1);
	int y2a  = HEIGHT / 2 + (int)(-(yceil + t2.y * plr->yaw)  * yscale2), y2b = HEIGHT / 2 + (int)(-(yfloor + t2.y * plr->yaw)  * yscale2);
	/* The same for the neighboring sector */
	int ny1a = HEIGHT / 2 + (int)(-(nyceil + t1.y * plr->yaw)  * yscale1), ny1b = HEIGHT / 2 + (int)(-(nyfloor + t1.y * plr->yaw) * yscale1);
	int ny2a = HEIGHT / 2 + (int)(-(nyceil + t2.y * plr->yaw)  * yscale2), ny2b = HEIGHT / 2 + (int)(-(nyfloor + t2.y * plr->yaw) * yscale2);
	int beginx = max(x1, sect.sx1), endx = min(x2, sect.sx2);
	if (push)
		engine_push_renderstack(eng->world->renderqueue, (t_item){portal, beginx, endx});
	unsigned r;
	t_scaler ya_int = Scaler_Init(x1, beginx, x2, y1a, y2a);
	t_scaler yb_int = Scaler_Init(x1, beginx, x2, y1b, y2b);
	t_scaler nya_int = Scaler_Init(x1, beginx, x2, ny1a, ny2a);
	t_scaler nyb_int = Scaler_Init(x1, beginx, x2, ny1b, ny2b);
	for(int x = beginx; x <= endx; ++x)
	{
		/* Calculate the Z coordinate for this point. (Only used for lighting.) */
		int z = ((x - x1) * (t2.y - t1.y) / (x2 - x1) + t1.y) * 8;
		/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
		int ya = scaler_next(&ya_int);
		int yb = scaler_next(&yb_int);
		int cya = clamp(ya, ytop[x], ybottom[x]); // top
		int cyb = clamp(yb, ytop[x], ybottom[x]); // bottom
		int txtx = (u0 * ((x2 - x) * t2.y) + u1 * ((x - x1) * t1.y)) / ((x2-x) * t2.y + (x - x1) * t1.y);
		t_image *tex = NULL;
		for(int y = ytop[x]; y <= ybottom[x] - 1; ++y)
		{
			if(y >= cya && y <= cyb)
			{
				y = cyb;
				continue;
			}
			float hei = y < cya ? yceil : yfloor;
			t_costil pnts = relative_map_coordinate_to_absolute(plr, hei, x, y);
			tex = y < cya ? eng->world->sectors_array[sect.sectorno].ceil_texture : eng->world->sectors_array[sect.sectorno].floor_texture;
			unsigned txtx = (pnts.x), txtz = (pnts.z);
			int offset = (((txtz % tex->height) * tex->width) + (txtx % tex->width)) * tex->channels;
			int8_t red = (tex->data)[offset];
			int8_t green = (tex->data)[offset + 1];
			int8_t blue = (tex->data)[offset + 2];
			int color = get_rgb((int)red, (int)green, (int)blue, 255);
			((int*)surf->pixels)[y * WIDTH + x] = color;
		}
		/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
		if (portal >= 0)
		{
			int nya = scaler_next(&nya_int);
			int nyb = scaler_next(&nyb_int);
			int cnya = clamp(nya, ytop[x], ybottom[x]);
			int cnyb = clamp(nyb, ytop[x], ybottom[x]);
			engine_vline_textured(eng, surf, (t_scaler)Scaler_Init(ya, cya, yb, 0, polygone->texture->height - 1) ,(t_fix_point_3d){x, cya, z}, (t_fix_point_3d){x, cnya-1, z}, txtx, eng->world->sectors_array[sect.sectorno].objects_array[obj_id].floor_wall_texture);
			ytop[x] = clamp(max(cya, cnya), ytop[x], HEIGHT - 1);
			engine_vline_textured(eng, surf, (t_scaler)Scaler_Init(ya, cnyb + 1, yb, 0, polygone->texture->height - 1) ,(t_fix_point_3d){x, cnyb + 1, z}, (t_fix_point_3d){x, cyb, z}, txtx, eng->world->sectors_array[sect.sectorno].objects_array[obj_id].floor_wall_texture);
			ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]);
		}
		else
			engine_vline_textured(eng, surf, (t_scaler)Scaler_Init(ya, cya, yb, 0, polygone->texture->height - 1) ,(t_fix_point_3d){x, cya + 1, z}, (t_fix_point_3d){x, cyb, z}, txtx, polygone->texture);
	}
	renderbox = (t_line){(t_point_3d){0, beginx,}, (t_point_3d){0, endx, }};
	int		i = 0;
	while (eng->world->sectors_array[sect.sectorno].objects_array[obj_id].particles[i].id == 1 && i < 128)
	{
		if (eng->world->sectors_array[sect.sectorno].objects_array[obj_id].particles[i].z > eng->world->sectors_array[sect.sectorno].floor &&
		eng->world->sectors_array[sect.sectorno].objects_array[obj_id].particles[i].z < eng->world->sectors_array[sect.sectorno].ceil)
			engine_render_particle(eng, surf, eng->world->sectors_array[sect.sectorno].objects_array[obj_id].particles[i],
					&eng->world->sectors_array[sect.sectorno].objects_array[obj_id], ytop, ybottom, plr, sect);
		i++;
	}
}

void		engine_render_particle(t_engine *eng, SDL_Surface *surf, t_wallobj particle,  t_object *obj, int *ytop, int *ybottom, t_player *plr, t_item sect)
{
	t_point_2d	t1;
	t_point_2d	t2;
	t_point_2d	c1;
	t_point_2d	c2;

	c1.x = particle.a.x - plr->position.x;
	c1.y = particle.a.y - plr->position.y;
	c2.x = particle.b.x - plr->position.x;
	c2.y = particle.b.y - plr->position.y;
	t1.x = c1.x * plr->sinangle - c1.y * plr->cosangle;
	t1.y = c1.x * plr->cosangle + c1.y * plr->sinangle;
	t2.x = c2.x * plr->sinangle - c2.y * plr->cosangle;
	t2.y = c2.x * plr->cosangle + c2.y * plr->sinangle;
	/* Is the wall at least partially in front of the player? */
	if(t1.y <= 0 && t2.y <= 0)
		return ;
	int u0 = 0, u1 = eng->sprites_buffer[4]->texture.height - 1;
	if(t1.y <= 0 || t2.y <= 0)
	{
		float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 60.f;
		// Find an intersection between the wall and the approximate edges of player's view
		t_point_2d i1 = Intersect(t1.x, t1.y, t2.x, t2.y, -nearside, nearz, -farside, farz);
		t_point_2d i2 = Intersect(t1.x, t1.y, t2.x, t2.y, nearside, nearz, farside, farz);
		t_point_2d org1 = {t1.x, t1.y}, org2 = {t2.x, t2.y};
		if(t1.y < nearz)
		{
			if(i1.y > 0)
				t1 = i1;
			else
				t1 = i2;
		}
		if(t2.y < nearz)
		{
			if(i1.y > 0)
				t2 = i1;
			else
				t2 = i2;
		}
		if(fabsf(t2.x - t1.x) > fabsf(t2.y - t1.y))
			u0 = (t1.x - org1.x) * (eng->sprites_buffer[4]->texture.height - 1) / (org2.x-org1.x), u1 = (t2.x - org1.x) * (eng->sprites_buffer[4]->texture.height - 1) / (org2.x - org1.x);
		else
			u0 = (t1.y - org1.y) * (eng->sprites_buffer[4]->texture.width - 1) / (org2.y-org1.y), u1 = (t2.y - org1.y) * (eng->sprites_buffer[4]->texture.width - 1) / (org2.y - org1.y);
	}
	/* Do perspective transformation */
	float xscale1 = (WIDTH * hfov) / t1.y, yscale1 = (HEIGHT * vfov) / t1.y;
	int x1 = WIDTH / 2 + (-t1.x * xscale1);
	float xscale2 = (WIDTH * hfov) / t2.y, yscale2 = (HEIGHT * vfov) / t2.y;
	int x2 = WIDTH / 2 + (-t2.x * xscale2);
	if(x1 >= x2 || x2 < sect.sx1 || x1 > sect.sx2)
		return; // Only render if it's visible
	/* Acquire the floor and ceiling heights, relative to where the player's view is */
	float yceil =  (particle.z + 8) - plr->position.z;
	float yfloor = (particle.z - 8) - plr->position.z;
	/* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
	int y1a  = HEIGHT / 2 + (int)(-(yceil + t1.y * plr->yaw) * yscale1), y1b = HEIGHT / 2 + (int)(-(yfloor + t1.y * plr->yaw)  * yscale1);
	int y2a  = HEIGHT / 2 + (int)(-(yceil + t2.y * plr->yaw)  * yscale2), y2b = HEIGHT / 2 + (int)(-(yfloor + t2.y * plr->yaw)  * yscale2);
	int beginx = max(x1, sect.sx1), endx = min(x2, sect.sx2);
	t_scaler ya_int = Scaler_Init(x1, beginx, x2, y1a, y2a);
	t_scaler yb_int = Scaler_Init(x1, beginx, x2, y1b, y2b);
	if (obj->portal == -1)
	{
		for(int x = beginx; x <= endx; ++x)
		{
			/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
			int ya = scaler_next(&ya_int);
			int yb = scaler_next(&yb_int);
			int cya = clamp(ya, ytop[x], ybottom[x]); // top
			int cyb = clamp(yb, ytop[x], ybottom[x]); // bottom
			int txtx = (u0 * ((x2 - x) * t2.y) + u1 * ((x - x1) * t1.y)) / ((x2 - x) * t2.y + (x - x1) * t1.y);
			engine_vline_textured(eng, surf, (t_scaler)Scaler_Init(ya, cya, yb, 0, eng->sprites_buffer[4]->texture.width - 1) ,(t_fix_point_3d){x, cya + 1, 0}, (t_fix_point_3d){x, cyb, 0}, txtx, &eng->sprites_buffer[4]->texture);
		}
	}
	else
	{
		for(int x = beginx; x <= endx; ++x)
		{
			/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
			int ya = scaler_next(&ya_int);
			int yb = scaler_next(&yb_int);
			int cya = clamp(ya, 0, WIDTH - 1); // top
			int cyb = clamp(yb, 0, WIDTH - 1); // bottom
			int txtx = (u0 * ((x2 - x) * t2.y) + u1 * ((x - x1) * t1.y)) / ((x2 - x) * t2.y + (x - x1) * t1.y);
			engine_vline_textured(eng, surf, (t_scaler)Scaler_Init(ya, cya, yb, 0, eng->sprites_buffer[4]->texture.width - 1) ,(t_fix_point_3d){x, cya + 1, 0}, (t_fix_point_3d){x, cyb, 0}, txtx, &eng->sprites_buffer[4]->texture);
		}
	}
}

void		engine_render_polygone(t_engine *eng, t_player *plr, t_polygone *wall, int *ytop, int *ybottom)
{
	t_polygone	a;
	t_point_2d	v1;
	t_point_2d	v2;
	t_point_2d	t1;
	t_point_2d	t2;

	v1.x = wall->vertices_array[0].x - plr->position.x;
	v1.y = wall->vertices_array[0].y - plr->position.y;
	v2.x = wall->vertices_array[1].x - plr->position.x;
	v2.y = wall->vertices_array[1].y - plr->position.y;
	a.vertices_array = (t_point_3d *)ft_memalloc(sizeof(t_point_3d) * 3);
	a.color = wall->color;
	t1.x = v1.x * plr->sinangle - v1.y * plr->cosangle;
	t1.y = v1.x * plr->cosangle + v1.y * plr->sinangle;
	t2.x = v2.x * plr->sinangle - v2.y * plr->cosangle;
	t2.y = v2.x * plr->cosangle + v2.y * plr->sinangle;
	/* Is the wall at least partially in front of the player? */
	if(t1.y <= 0 && t2.y <= 0)
		return ;
	/* If it's partially behind the player, clip it against player's view frustrum */
	if(t1.y <= 0 || t2.y <= 0)
	{
		float nearz = 1e-4f, farz = 4, nearside = 1e-5f, farside = 20.f;
		// Find an intersection between the wall and the approximate edges of player's view
		t_point_2d i1 = Intersect(t1.x, t1.y, t2.x, t2.y, -nearside, nearz, -farside, farz);
		t_point_2d i2 = Intersect(t1.x, t1.y, t2.x, t2.y, nearside, nearz, farside, farz);
		if (t1.y < nearz)
		{
			if (i1.y >= 0)
				t1 = i1;
			else
				t1 = i2;
		}
		if (t2.y < nearz)
		{
			if (i1.y >= 0)
				t2 = i1;
			else
				t2 = i2;
		}
	}
	/* Do perspective transformation */
	float xscale1 = hfov / t1.y, yscale1 = vfov / t1.y;
	int x1 = WIDTH / 2 - (int)(t1.x * xscale1);
	float xscale2 = hfov / t2.y, yscale2 = vfov / t2.y;
	int x2 = WIDTH / 2 - (int)(t2.x * xscale2);
	if(x1 >= x2 || x2 <= 0 || x1 > WIDTH)
		return; // Only render if it's visible
	float yceil = wall->vertices_array[0].z - plr->position.z;
	float yfloor = eng->world->sectors_array[plr->cursector].floor - plr->position.z;
	int y1a  = HEIGHT / 2 - (int)((yceil + t1.y * plr->yaw) * yscale1),  y1b = HEIGHT / 2 - (int)((yfloor + t1.y * plr->yaw)  * yscale1);
	int y2a  = HEIGHT / 2 - (int)((yceil + t2.y * plr->yaw)  * yscale2),  y2b = HEIGHT / 2 - (int)((yfloor + t2.y * plr->yaw)  * yscale2);
	int beginx = max(x1, 0), endx = min(x2, WIDTH - 1);
	int ya1 = (beginx - x1) * (y2a - y1a) / (x2-x1) + y1a, cya1 = clamp(ya1, ytop[beginx], ybottom[beginx]); // top
	int yb1 = (beginx - x1) * (y2b - y1b) / (x2-x1) + y1b, cyb1 = clamp(yb1, ytop[beginx], ybottom[beginx]); // bottom
	int z1 = ((beginx - x1) * (t2.y - t1.y) / (x2 - x1) + t1.y) * 100;
	int ya2 = (endx - x1) * (y2a - y1a) / (x2-x1) + y1a, cya2 = clamp(ya2, ytop[endx], ybottom[endx]); // top
	int yb2 = (endx - x1) * (y2b - y1b) / (x2-x1) + y1b, cyb2 = clamp(yb2, ytop[endx], ybottom[endx]); // bottom
	int z2 = ((endx - x1) * (t2.y - t1.y) / (x2 - x1) + t1.y) * 100;
	a.vertices_array[0].x = beginx;
	a.vertices_array[0].y = cya1;
	a.vertices_array[0].z = z1;
	a.vertices_array[1].x = beginx;
	a.vertices_array[1].y = cyb1;
	a.vertices_array[1].z = z1;
	a.vertices_array[2].x = endx;
	a.vertices_array[2].y = cya2;
	a.vertices_array[2].z = z2;
	engine_triangle(eng, plr, &a);
	//bresenham_line(eng, &(t_point_3d){0, a->vertices_array[0].x, a->vertices_array[0].y}, (t_point_3d){a->vertices_array[1].x, a->vertices_array[1].y}, get_rgb(((a->color) >> 16), ((a->color) >> 8), ((a->color)), 255));
	//bresenham_line(eng, &(t_point_3d){0, a->vertices_array[1].x, a->vertices_array[1].y}, (t_point_3d){a->vertices_array[2].x, a->vertices_array[2].y}, get_rgb(((a->color) >> 16), ((a->color) >> 8), ((a->color)), 255));
	//bresenham_line(eng, &(t_point_3d){a->vertices_array[2].x, a->vertices_array[2].y}, (t_point_3d){a->vertices_array[0].x, a->vertices_array[0].y}, get_rgb(((a->color) >> 16), ((a->color) >> 8), ((a->color)), 255));
	//triangle_lines(a, eng);
	//SDL_RenderDrawLine(eng->ren, a->vertices_array[0].x, a->vertices_array[0].y, a->vertices_array[1].x, a->vertices_array[1].y);
	//SDL_RenderDrawLine(eng->ren, a->vertices_array[2].x, a->vertices_array[2].y, a->vertices_array[1].x, a->vertices_array[1].y);
	//SDL_RenderDrawLine(eng->ren, a->vertices_array[0].x, a->vertices_array[0].y, a->vertices_array[2].x, a->vertices_array[2].y);
	//engine_draw_line(eng, (t_point_2d){a->vertices_array[1].x, a->vertices_array[1].y}, (t_point_2d){a->vertices_array[2].x, a->vertices_array[2].y}, get_rgb(((a->color) >> 16), ((a->color) >> 8), ((a->color)), 255));
	a.vertices_array[0].x = endx;
	a.vertices_array[0].y = cya2;
	a.vertices_array[0].z = z2;
	a.vertices_array[1].x = endx;
	a.vertices_array[1].y = cyb2;
	a.vertices_array[1].z = z2;
	a.vertices_array[2].x = beginx;
	a.vertices_array[2].y = cyb1;
	a.vertices_array[2].z = z1;
	engine_triangle(eng, plr, &a);
	//triangle_lines(a, eng);
	//engine_draw_line(eng, (t_point_2d){a->vertices_array[0].x, a->vertices_array[0].y}, (t_point_2d){a->vertices_array[1].x, a->vertices_array[1].y}, get_rgb(((a->color) >> 16), ((a->color) >> 8), ((a->color)), 255));
	//engine_draw_line(eng, (t_point_2d){a->vertices_array[1].x, a->vertices_array[1].y}, (t_point_2d){a->vertices_array[2].x, a->vertices_array[2].y}, get_rgb(((a->color) >> 16), ((a->color) >> 8), ((a->color)), 255));
	//engine_draw_line(eng, (t_point_2d){a->vertices_array[2].x, a->vertices_array[2].y}, (t_point_2d){a->vertices_array[0].x, a->vertices_array[0].y}, get_rgb(((a->color) >> 16), ((a->color) >> 8), ((a->color)), 255));
	//SDL_RenderDrawLine(eng->ren, a->vertices_array[0].x, a->vertices_array[0].y, a->vertices_array[1].x, a->vertices_array[1].y);
	//SDL_RenderDrawLine(eng->ren, a->vertices_array[2].x, a->vertices_array[2].y, a->vertices_array[1].x, a->vertices_array[1].y);
	//SDL_RenderDrawLine(eng->ren, a->vertices_array[0].x, a->vertices_array[0].y, a->vertices_array[2].x, a->vertices_array[2].y);
	//engine_triangle(eng, plr, a);
}

void		engine_render_frame(t_engine *eng, SDL_Surface *surf)
{
	SDL_Texture	*texture;

	texture = SDL_CreateTextureFromSurface(eng->ren, surf);
	SDL_RenderClear(eng->ren);
	SDL_RenderCopy(eng->ren, texture, NULL, NULL);
	SDL_RenderPresent(eng->ren);
	SDL_DestroyTexture(texture);
}

void		sdl_put_pixel(SDL_Surface *surf, int x, int y, int color)
{
	int		bpp;
	Uint8	*p;

	bpp = surf->format->BytesPerPixel;
	p = (Uint8*) surf->pixels + y * surf->pitch + x * bpp;
	*(int *)p = color;
}

void		engine_vline(t_engine *eng, SDL_Surface *surf, t_fix_point_3d a, t_fix_point_3d b, int color)
{
	int		y1;
	int		y2;
	int		*pix = (int*) surf->pixels;

	y1 = clamp(a.y, 0, HEIGHT - 1);
	y2 = clamp(b.y, 0, HEIGHT - 1);
	if(y2 == y1)
		pix[y1 * WIDTH + a.x] = color;
	else if(y2 > y1)
	{
		pix[y1 * WIDTH + a.x] = 0xFF;
		for(int y = y1 + 1; y < y2; ++y)
			pix[y * WIDTH + a.x] = color;
		pix[y2 * WIDTH + a.x] = 0xFF;
	}
}

t_costil	relative_map_coordinate_to_absolute(t_player *plr, float map_y, float screen_x, float screen_y)
{
	float z = (map_y * HEIGHT * vfov) / ((HEIGHT / 2 - screen_y) - (plr->yaw * HEIGHT * vfov));
	float x = z * (WIDTH / 2 - screen_x) / (WIDTH * hfov);
	return (ceiling_floor_screen_coordinates_to_map_coordinates(plr, z, x));
}

t_costil	ceiling_floor_screen_coordinates_to_map_coordinates(t_player *plr, float tz, float tx)
{
	t_costil	res;

	float rtx = (tz) * plr->cosangle + (tx) * plr->sinangle;
	float rtz = (tz) * plr->sinangle - (tx) * plr->cosangle;
	res.x = rtx + plr->position.x;
	res.z = rtz + plr->position.y;
	return (res);
}
