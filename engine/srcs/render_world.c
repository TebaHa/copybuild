/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:42:08 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/15 00:08:38 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int			get_rgb(int r, int g, int b, int a)
{
	return (((((int)r) << 24) & 0xFF000000) |
	((((int)g) << 16) & 0x00FF0000) |
	(((b) << 8) & 0x0000FF00) | (((a)) & 0x000000FF));
}

void		engine_render_world_data(t_engine *eng, t_player *plr, t_wall_help2 *data)
{
	int		i;

	i = 0;
	data->prev = -1;
	data->plr = plr;
	data->sect = (t_item){plr->cursector, 0, WIDTH - 1};
	while (i < WIDTH)
	{
		data->ytop[i] = 0;
		data->ybottom[i] = HEIGHT;
		i++;
	}
}

void		engine_render_world_help(t_engine *eng, t_player *plr,
			SDL_Surface *surf, t_wall_help2 *data)
{
	int		i;

	while (((data->sect = engine_pop_renderstack(
	eng->world->renderstack)).sectorno >= 0))
	{
		i = 0;
		while (i < eng->world->sectors_array[data->sect.sectorno].objects_count)
		{
			data->portal = eng->world->sectors_array
			[data->sect.sectorno].objects_array[i].portal;
			data->polygone = eng->world->sectors_array
			[data->sect.sectorno].objects_array[i].polies_array;
			data->obj_id = i;
			engine_render_wall(eng, surf, data);
			i++;
		}
		data->prev = data->sect.sectorno;
	}
}

void		engine_render_world(t_engine *eng, t_player plr, SDL_Surface *surf)
{
	t_wall_help2 data;

	SDL_LockSurface(surf);
	engine_render_world_data(eng, &plr, &data);
	engine_push_renderstack(eng->world->renderstack, data.sect);
	one_dim_zbuffers_copy(&eng->world->sectors_array[data.sect.sectorno].
	item_sprts, data.ytop, data.ybottom);
	eng->world->sectors_array[data.sect.sectorno].
	item_sprts.sect_id = data.sect;
	engine_push_spriterenderstack(eng->world->sprite_renderstack,
	&eng->world->sectors_array[data.sect.sectorno].item_sprts);
	engine_render_world_help(eng, &plr, surf, &data);
	engine_render_sprites(eng, &plr, surf);
	engine_clear_renderstack(eng->world->renderstack);
	engine_clear_spriterenderstack(eng->world->sprite_renderstack);
	SDL_UnlockSurface(surf);
}

void		one_dim_zbuffers_copy(t_item_sprts *sprt, int *ytop, int *ybottom)
{
	int		i;

	i = 0;
	while (i < WIDTH)
	{
		sprt->ytop[i] = ytop[i];
		sprt->ybottom[i] = ybottom[i];
		i++;
	}
}

void		engine_render_particle(t_engine *eng, SDL_Surface *surf, t_wallobj *particle, t_object *obj, t_player *plr, t_item sect)
{
	t_point_2d	t1;
	t_point_2d	t2;
	t_point_2d	c1;
	t_point_2d	c2;

	c1.x = particle->a.x - plr->position.x;
	c1.y = particle->a.y - plr->position.y;
	c2.x = particle->b.x - plr->position.x;
	c2.y = particle->b.y - plr->position.y;
	t1.x = c1.x * plr->sinangle - c1.y * plr->cosangle;
	t1.y = c1.x * plr->cosangle + c1.y * plr->sinangle;
	t2.x = c2.x * plr->sinangle - c2.y * plr->cosangle;
	t2.y = c2.x * plr->cosangle + c2.y * plr->sinangle;
	if(t1.y <= 0 && t2.y <= 0)
		return ;
	int u0 = 0, u1 = particle->texture->surface[particle->frame_num]->h - 1;
	if(t1.y <= 0 || t2.y <= 0)
	{
		float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 60.f;
		t_point_2d i1 = intersect((t_point_2d){t1.x, t1.y}, (t_point_2d){t2.x, t2.y},
		(t_point_2d){-nearside, nearz}, (t_point_2d){-farside, farz});
		t_point_2d i2 = intersect((t_point_2d){t1.x, t1.y}, (t_point_2d){t2.x, t2.y},
		(t_point_2d){nearside, nearz}, (t_point_2d){farside, farz});
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
			u0 = (t1.x - org1.x) * (particle->texture->surface[particle->frame_num]->h - 1) / (org2.x-org1.x), u1 = (t2.x - org1.x) * (particle->texture->surface[particle->frame_num]->h - 1) / (org2.x - org1.x);
		else
			u0 = (t1.y - org1.y) * (particle->texture->surface[particle->frame_num]->w - 1) / (org2.y-org1.y), u1 = (t2.y - org1.y) * (particle->texture->surface[particle->frame_num]->w - 1) / (org2.y - org1.y);
	}
	float xscale1 = (WIDTH * hfov) / t1.y, yscale1 = (HEIGHT * vfov) / t1.y;
	int x1 = WIDTH / 2 + (-t1.x * xscale1);
	float xscale2 = (WIDTH * hfov) / t2.y, yscale2 = (HEIGHT * vfov) / t2.y;
	int x2 = WIDTH / 2 + (-t2.x * xscale2);
	if(x1 >= x2 || x2 < sect.sx1 || x1 > sect.sx2)
		return;
	float yceil = (particle->z + particle->texture->surface[particle->frame_num]->h / 4) - plr->position.z;
	float yfloor = (particle->z - particle->texture->surface[particle->frame_num]->h / 4) - plr->position.z;
	int y1a  = HEIGHT / 2 + (int)(-(yceil + t1.y * plr->yaw) * yscale1), y1b = HEIGHT / 2 + (int)(-(yfloor + t1.y * plr->yaw)  * yscale1);
	int y2a  = HEIGHT / 2 + (int)(-(yceil + t2.y * plr->yaw)  * yscale2), y2b = HEIGHT / 2 + (int)(-(yfloor + t2.y * plr->yaw)  * yscale2);
	int beginx = max(x1, sect.sx1), endx = min(x2, sect.sx2);
	t_scaler ya_int = scaler_init((float [5]){x1, beginx, x2, y1a, y2a});
	t_scaler yb_int = scaler_init((float [5]){x1, beginx, x2, y1b, y2b});
	for(int x = beginx; x <= endx; ++x)
	{
		int ya = scaler_next(&ya_int);
		int yb = scaler_next(&yb_int);
		int cya = clamp(ya, eng->world->sectors_array[sect.sectorno].item_sprts.ytop[x], eng->world->sectors_array[sect.sectorno].item_sprts.ybottom[x]);
		int cyb = clamp(yb, eng->world->sectors_array[sect.sectorno].item_sprts.ytop[x], eng->world->sectors_array[sect.sectorno].item_sprts.ybottom[x]);
		int txtx = (u0 * ((x2 - x) * t2.y) + u1 * ((x - x1) * t1.y)) / ((x2 - x) * t2.y + (x - x1) * t1.y);
		engine_vline_textured_surface(surf, (t_scaler)scaler_init((float [5]){ya, cya, yb, 0, particle->texture->surface[particle->frame_num]->w - 1}) ,(t_fix_point_3d){x, cya + 1, 0}, (t_fix_point_3d){x, cyb, 0}, txtx, particle->texture->surface[particle->frame_num]);
	}
	if (particle->texture->a_state == ANIMATE)
	{
		if (((particle->timer % particle->texture->frames_delay) == 0) && (particle->frame_num < particle->texture->frames_num - 1))
			particle->frame_num++;
		else
			particle->timer++;
	}
}

void		engine_render_frame(t_engine *eng, SDL_Surface *surf)
{
	SDL_Texture	*texture;

	texture = SDL_CreateTextureFromSurface(eng->ren, surf);
	SDL_RenderCopy(eng->ren, texture, NULL, NULL);
	SDL_DestroyTexture(texture);
}

void		engine_present_and_clear_frame(t_engine *eng)
{
	SDL_RenderPresent(eng->ren);
	SDL_RenderClear(eng->ren);
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

t_costil	relative_map_coordinate_to_absolute
			(t_player *plr, float map_y, float screen_x, float screen_y)
{
	float z = (map_y * HEIGHT * vfov) / ((HEIGHT / 2 - screen_y) - (plr->yaw * HEIGHT * vfov));
	float x = z * (WIDTH / 2 - screen_x) / (WIDTH * hfov);
	return (ceiling_floor_screen_coordinates_to_map_coordinates(plr, z, x));
}

t_costil	ceiling_floor_screen_coordinates_to_map_coordinates
			(t_player *plr, float tz, float tx)
{
	t_costil	res;

	float rtx = (tz) * plr->cosangle + (tx) * plr->sinangle;
	float rtz = (tz) * plr->sinangle - (tx) * plr->cosangle;
	res.x = rtx + plr->position.x;
	res.z = rtz + plr->position.y;
	return (res);
}
