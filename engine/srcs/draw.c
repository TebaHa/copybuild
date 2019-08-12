/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:42:08 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/12 19:37:32 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int		get_rgb(int r, int g, int b, int a)
{
	return (((((int)r) << 24) & 0xFF000000) | ((((int)g) << 16) & 0x00FF0000) | (((b) << 8) & 0x0000FF00) | (((a)) & 0x000000FF));
}

void		engine_create_renderstack(t_engine *eng, int render_id, int *rendered)
{
	int		i;
	int		sect;

	i = 0;
	engine_push_renderstack(eng->world->renderqueue, render_id);
	rendered[render_id] = 1;
	while (i < 4)
	{
		sect = eng->world->sectors_array[render_id].objects_array[i].portal;
		if (sect >= 0 && rendered[sect] == 0)
			engine_create_renderstack(eng, sect, rendered);
		i++;
	}
}

void		engine_render_world(t_engine *eng, t_player *plr, int *rendered)
{
	int			ytop[WIDTH] = {0};
	int			ybottom[WIDTH];
	unsigned	x;
	int			sect_id;
	int			i;

	x = 0;
	sect_id = plr->cursector;
	SDL_LockSurface(eng->surface);
	while (x < WIDTH)
	{
		ybottom[x] = HEIGHT - 1;
		x++;
	}
	i = 0;
	engine_push_renderstack(eng->world->renderqueue, sect_id);
	while (((sect_id = engine_pop_renderstack(eng->world->renderqueue)) >= 0) && rendered[sect_id] == 0)
	{
		while (i < eng->world->sectors_array[sect_id].objects_count)
		{
			engine_render_wall(eng, plr, eng->world->sectors_array[sect_id].objects_array[i].polies_array,
				ytop, ybottom);
			i++;
		}
		rendered[sect_id] = 1;
	}
	engine_clear_renderstack(eng->world->renderqueue);
	SDL_UnlockSurface(eng->surface);
}

void		engine_render_wall(t_engine *eng, t_player *plr, t_polygone *wall, int *ytop, int *ybottom)
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
	/* Rotate them around the player's view */
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
// void		engine_render_polygone(t_engine *eng, t_polygone *polygone, t_player *plr, int *ytop, int *ybottom, int portal, int *rendered)
// {
// 	t_point_2d	v1;
// 	t_point_2d	v2;
// 	t_point_2d	t1;
// 	t_point_2d	t2;

// 	v1.x = polygone->vertices_array[0].x - plr->position.x;
// 	v1.y = polygone->vertices_array[0].y - plr->position.y;
// 	v2.x = polygone->vertices_array[1].x - plr->position.x;
// 	v2.y = polygone->vertices_array[1].y - plr->position.y;
// 	/* Rotate them around the player's view */
// 	t1.x = v1.x * plr->sinangle - v1.y * plr->cosangle;
// 	t1.y = v1.x * plr->cosangle + v1.y * plr->sinangle;
// 	t2.x = v2.x * plr->sinangle - v2.y * plr->cosangle;
// 	t2.y = v2.x * plr->cosangle + v2.y * plr->sinangle;
// 	/* Is the wall at least partially in front of the player? */
// 	if(t1.y <= 0 && t2.y <= 0)
// 		return ;
// 	/* If it's partially behind the player, clip it against player's view frustrum */
// 	if(t1.y <= 0 || t2.y <= 0)
// 	{
// 		float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
// 		// Find an intersection between the wall and the approximate edges of player's view
// 		t_point_2d i1 = Intersect(t1.x, t1.y, t2.x, t2.y, -nearside, nearz, -farside, farz);
// 		t_point_2d i2 = Intersect(t1.x, t1.y, t2.x, t2.y, nearside, nearz, farside, farz);
// 		if(t1.y < nearz)
// 		{
// 			if(i1.y > 0)
// 				t1 = i1;
// 			else
// 				t1 = i2;
// 		}
// 		if(t2.y < nearz)
// 		{
// 			if(i1.y > 0)
// 				t2 = i1;
// 			else
// 				t2 = i2;
// 		}
// 	}
// 	/* Do perspective transformation */
// 	float xscale1 = hfov / t1.y, yscale1 = vfov / t1.y;
// 	int x1 = WIDTH / 2 - (int)(t1.x * xscale1);
// 	float xscale2 = hfov / t2.y, yscale2 = vfov / t2.y;
// 	int x2 = WIDTH / 2 - (int)(t2.x * xscale2);
// 	if(x1 >= x2 || x2 < 0 || x1 > WIDTH - 1)
// 		return; // Only render if it's visible
// 	/* Acquire the floor and ceiling heights, relative to where the player's view is */
// 	float yceil = polygone->vertices_array[0].z - plr->position.z;
// 	float yfloor = eng->world->sectors_array[plr->cursector].floor - plr->position.z;
// 	/* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
// 	float nyceil = 0, nyfloor = 0;
// 	if(portal >= 0) // Is another sector showing through this portal?
// 	{
// 		nyceil  = eng->world->sectors_array[portal].ceil - plr->position.z;
// 		nyfloor = eng->world->sectors_array[portal].floor - plr->position.z;
// 		engine_push_renderstack(eng->world->renderqueue, portal);
// 	}
// 	int y1a  = HEIGHT / 2 - (int)((yceil + t1.y * plr->yaw) * yscale1),  y1b = HEIGHT / 2 - (int)((yfloor + t1.y * plr->yaw)  * yscale1);
// 	int y2a  = HEIGHT / 2 - (int)((yceil + t2.y * plr->yaw)  * yscale2),  y2b = HEIGHT / 2 - (int)((yfloor + t2.y * plr->yaw)  * yscale2);
// 	/* The same for the neighboring sector */
// 	int ny1a = HEIGHT / 2 - (int)((nyceil + t1.y * plr->yaw)  * yscale1), ny1b = HEIGHT / 2 - (int)((nyfloor + t1.y * plr->yaw) * yscale1);
// 	int ny2a = HEIGHT / 2 - (int)((nyceil + t2.y * plr->yaw)  * yscale2), ny2b = HEIGHT / 2 - (int)((nyfloor + t2.y * plr->yaw) * yscale2);
// 	int beginx = max(x1, 0), endx = min(x2, WIDTH - 1);
// 	for(int x = beginx; x <= endx; ++x)
// 	{
// 		/* Calculate the Z coordinate for this point. (Only used for lighting.) */
// 		int z = ((x - x1) * (t2.y - t1.y) / (x2 - x1) + t1.y) * 0.1;
// 		/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
// 		int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a, cya = clamp(ya, ytop[x], ybottom[x]); // top
// 		int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b, cyb = clamp(yb, ytop[x], ybottom[x]); // bottom
// 		/* Render ceiling: everything above this sector's ceiling height. */
// 		engine_draw_line(eng, (t_point_2d){x, ytop[x]}, (t_point_2d){x, cya - 1}, get_rgb(173, 216, 230, 254));
// 		/* Render floor: everything below this sector's floor height. */
// 		engine_draw_line(eng, (t_point_2d){x, cyb + 1}, (t_point_2d){x, ybottom[x]}, get_rgb(218, 165, 32, 255));
// 		/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
// 		unsigned r = polygone->color * (255 - z);
// 		if (portal >= 0)
// 		{
// 			int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a, cnya = clamp(nya, ytop[x],ybottom[x]);
// 			int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b, cnyb = clamp(nyb, ytop[x],ybottom[x]);
// 			/* If our ceiling is higher than their ceiling, render upper wall */
// 			engine_draw_line(eng, (t_point_2d){x, cya}, (t_point_2d){x, cnya - 1}, x == x1 || x == x2 ? 0 : get_rgb(255, 0, 0, 255));
// 			ytop[x] = clamp(max(cya, cnya), ytop[x], HEIGHT - 1);// Shrink the remaining window below these ceilings
// 			/* If our floor is lower than their floor, render bottom wall */
// 			engine_draw_line(eng, (t_point_2d){x, cnyb + 1}, (t_point_2d){x, cyb}, x == x1 || x == x2 ? 0 : get_rgb(255, 0, 0, 255));
// 			ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]);
// 		}
// 		else
// 			engine_draw_line(eng, (t_point_2d){x, cya}, (t_point_2d){x, cyb},  x == x1 || x == x2 ? 0x000000FF : get_rgb(((r) >> 16), ((r) >> 8), ((r)), 255));
// 	}
// }

void	engine_clear_frame(t_engine *eng)
{
	SDL_LockSurface(eng->surface);
	SDL_memset(eng->surface->pixels, 8947848, eng->surface->h * eng->surface->pitch);
	SDL_UnlockSurface(eng->surface);
}

void	engine_render_frame(t_engine *eng)
{
	SDL_Texture	*texture;

	texture = SDL_CreateTextureFromSurface(eng->ren, eng->surface);
	SDL_RenderClear(eng->ren);
	SDL_RenderCopy(eng->ren, texture, NULL, NULL);
	SDL_RenderPresent(eng->ren);
	SDL_DestroyTexture(texture);
}

void	sdl_put_pixel(SDL_Surface *surf, int x, int y, int color)
{
	int		bpp;
	Uint8	*p;

	bpp = surf->format->BytesPerPixel;
	p = (Uint8*) surf->pixels + y* surf->pitch + x * bpp;
	*(int *)p = color;
}
