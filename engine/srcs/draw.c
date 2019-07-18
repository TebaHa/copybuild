/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:42:08 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/18 18:53:08 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

int		get_rgb(char r, char g, char b)
{
	return (((int)r << 24) | ((int)g << 16) | ((int)b << 8) | 0x000000ff);
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
		sect = eng->world->sectors_array[render_id].objects_array[i].sector;
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
	engine_create_renderstack(eng, sect_id, rendered);
	while (((sect_id = engine_pop_renderstack(eng->world->renderqueue)) >= 0))
	{
		i = 0;
		while (i < 4)
		{
			engine_render_polygone(eng, eng->world->sectors_array[sect_id].objects_array[i].polies_array[0],
				plr, ytop, ybottom, eng->world->sectors_array[sect_id].objects_array[i].sector);
			i++;
		}
	}
	engine_clear_renderstack(eng->world->renderqueue);
	SDL_UnlockSurface(eng->surface);
}

void		engine_render_polygone(t_engine *eng, t_polygone polygone, t_player *plr, int *ytop, int *ybottom, int portal)
{
	float vx1 = polygone.vertices[0].x - plr->position.x, vy1 = polygone.vertices[0].y - plr->position.y;
	float vx2 = polygone.vertices[3].x - plr->position.x, vy2 = polygone.vertices[3].y - plr->position.y;
	/* Rotate them around the player's view */
	float tx1 = vx1 * plr->sinangle - vy1 * plr->cosangle,  tz1 = vx1 * plr->cosangle + vy1 * plr->sinangle;
	float tx2 = vx2 * plr->sinangle - vy2 * plr->cosangle,  tz2 = vx2 * plr->cosangle + vy2 * plr->sinangle;
	/* Is the wall at least partially in front of the player? */
	if(tz1 <= 0 && tz2 <= 0)
		return;
	/* If it's partially behind the player, clip it against player's view frustrum */
	if(tz1 <= 0 || tz2 <= 0)
	{
		float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
		// Find an intersection between the wall and the approximate edges of player's view
		t_point_2d i1 = Intersect(tx1,tz1,tx2,tz2, -nearside,nearz, -farside, farz);
		t_point_2d i2 = Intersect(tx1,tz1,tx2,tz2, nearside,nearz, farside, farz);
		if(tz1 < nearz)
		{
			if(i1.y > 0)
			{
				tx1 = i1.x;
				tz1 = i1.y;
			}
			else
			{
				tx1 = i2.x;
				tz1 = i2.y;
			}
		}
		if(tz2 < nearz)
		{
			if(i1.y > 0)
			{
				tx2 = i1.x;
				tz2 = i1.y;
			}
			else
			{
				tx2 = i2.x;
				tz2 = i2.y;
			}
		}
	}
	/* Do perspective transformation */
	float xscale1 = hfov / tz1, yscale1 = vfov / tz1;
	int x1 = WIDTH / 2 - (int)(tx1 * xscale1);
	float xscale2 = hfov / tz2, yscale2 = vfov / tz2;
	int x2 = WIDTH / 2 - (int)(tx2 * xscale2);
	if(x1 >= x2 || x2 < 0 || x1 > WIDTH - 1)
		return; // Only render if it's visible
	/* Acquire the floor and ceiling heights, relative to where the player's view is */
	float yceil = polygone.vertices[0].z - plr->position.z;
	float yfloor = polygone.vertices[1].z - plr->position.z;
	/* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
	float nyceil = 0, nyfloor = 0;
	if(portal >= 0) // Is another sector showing through this portal?
	{
		nyceil  = 60 - plr->position.z;
		nyfloor = 0 - plr->position.z;
	}
	int y1a  = HEIGHT / 2 - (int)(Yaw(yceil, tz1) * yscale1),  y1b = HEIGHT / 2 - (int)(Yaw(yfloor, tz1) * yscale1);
	int y2a  = HEIGHT / 2 - (int)(Yaw(yceil, tz2) * yscale2),  y2b = HEIGHT / 2 - (int)(Yaw(yfloor, tz2) * yscale2);
	/* The same for the neighboring sector */
	int ny1a = HEIGHT / 2 - (int)(Yaw(nyceil, tz1) * yscale1), ny1b = HEIGHT / 2 - (int)(Yaw(nyfloor, tz1) * yscale1);
	int ny2a = HEIGHT / 2 - (int)(Yaw(nyceil, tz2) * yscale2), ny2b = HEIGHT / 2 - (int)(Yaw(nyfloor, tz2) * yscale2);
	int beginx = max(x1, 0), endx = min(x2, WIDTH - 1);
	for(int x = beginx; x <= endx; ++x)
	{
		/* Calculate the Z coordinate for this point. (Only used for lighting.) */
		//int z = ((x - x1) * (tz2 - tz1) / (x2 - x1) + tz1) * 8;
		/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
		int ya = (x - x1) * (y2a - y1a) / (x2-x1) + y1a, cya = clamp(ya, ytop[x], ybottom[x]); // top
		int yb = (x - x1) * (y2b - y1b) / (x2-x1) + y1b, cyb = clamp(yb, ytop[x], ybottom[x]); // bottom
		/* Render ceiling: everything above this sector's ceiling height. */
		engine_draw_line(eng, (t_point_2d){x, ytop[x]}, (t_point_2d){x, cya - 1}, get_rgb((char)0, (char)0, (char)255));
		/* Render floor: everything below this sector's floor height. */
		engine_draw_line(eng, (t_point_2d){x, cyb + 1}, (t_point_2d){x, ybottom[x]}, get_rgb((char)218, (char)165, (char)32));
		/* There's no neighbor. Render wall from top (cya = ceiling level) to bottom (cyb = floor level). */
		//unsigned r = 0x010101 * (255 - z);
		if (portal >= 0)
		{
			int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a, cnya = clamp(nya, ytop[x],ybottom[x]);
			int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b, cnyb = clamp(nyb, ytop[x],ybottom[x]);
			/* If our ceiling is higher than their ceiling, render upper wall */
			engine_draw_line(eng, (t_point_2d){x, cya}, (t_point_2d){x, cnya - 1}, x == x1 || x == x2 ? 0xFFFFFFFF : get_rgb((char)0, (char)0, (char)0));
			ytop[x] = clamp(max(cya, cnya), ytop[x], HEIGHT - 1);// Shrink the remaining window below these ceilings
			/* If our floor is lower than their floor, render bottom wall */
			engine_draw_line(eng, (t_point_2d){x, cnyb + 1}, (t_point_2d){x, cyb}, x == x1 || x == x2 ? 0xFFFFFFFF : get_rgb((char)0, (char)0, (char)0));
			ybottom[x] = clamp(min(cyb, cnyb), 0, ybottom[x]);
		}
		else
			engine_draw_line(eng, (t_point_2d){x, cya}, (t_point_2d){x, cyb},  x == x1 || x == x2 ? 0xFFFFFFFF : get_rgb((char)210, (char)105, (char)30));
	}
}

void		engine_draw_line(t_engine *eng, t_point_2d a, t_point_2d b, int color)
{
	float			len;
	float			deltax;
	float			deltay;
	unsigned long	x;
	unsigned long	y;
	int				i;

	len = (fabs(b.x - a.x) > fabs(b.y - a.y)) ? fabs(b.x - a.x) : fabs(b.y - a.y);
	if (len > -0.0f && len < 0.0f)
	deltax = (b.x - a.x) / len;
	deltay = (b.y - a.y) / len;
	i = 0;
	while (i < (int)len)
	{
		a.x += deltax;
		a.y += deltay;
		x = (int)(a.x);
		y = (int)(a.y);
		if ((a.x) < WIDTH && (a.y) < HEIGHT)
			sdl_put_pixel(eng->surface, (a.x), (a.y), color);
		i++;
	}
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
	*(Uint32*)p = color;
}
