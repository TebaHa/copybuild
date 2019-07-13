/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:42:08 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/12 18:09:25 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void		engine_render_sector(t_engine *eng, t_sector *sect, t_player *plr)
{
	int		i;
	int ytop[WIDTH] = {0}, ybottom[WIDTH];
	for(unsigned x=0; x<WIDTH; ++x) ybottom[x] = HEIGHT-1;

	i = 0;
	while (i < 4)
	{
		engine_render_polygone(eng, sect->objects_array[i].polies_array[0], plr, ytop, ybottom);
		i++;
	}
}

void		engine_render_polygone(t_engine *eng, t_polygone polygone, t_player *plr, int *ytop, int *ybottom)
{
	float vx1 = polygone.vertices[0].x - plr->position.x, vy1 = polygone.vertices[0].y - plr->position.y;
	float vx2 = polygone.vertices[3].x - plr->position.x, vy2 = polygone.vertices[3].y - plr->position.y;
	/* Rotate them around the player's view */
	float pcos = cosf(plr->angle), psin = sinf(plr->angle);
	float tx1 = vx1 * psin - vy1 * pcos,  tz1 = vx1 * pcos + vy1 * psin;
	float tx2 = vx2 * psin - vy2 * pcos,  tz2 = vx2 * pcos + vy2 * psin;
	/* Is the wall at least partially in front of the player? */
	if(tz1 <= 0 && tz2 <= 0) return;
	/* If it's partially behind the player, clip it against player's view frustrum */
	if(tz1 <= 0 || tz2 <= 0)
	{
		float nearz = 1e-4f, farz = 5, nearside = 1e-5f, farside = 20.f;
		// Find an intersection between the wall and the approximate edges of player's view
		struct xy i1 = Intersect(tx1,tz1,tx2,tz2, -nearside,nearz, -farside, farz);
		struct xy i2 = Intersect(tx1,tz1,tx2,tz2,  nearside,nearz,  farside, farz);
		if(tz1 < nearz) { if(i1.y > 0) { tx1 = i1.x; tz1 = i1.y; } else { tx1 = i2.x; tz1 = i2.y; } }
		if(tz2 < nearz) { if(i1.y > 0) { tx2 = i1.x; tz2 = i1.y; } else { tx2 = i2.x; tz2 = i2.y; } }
	}
	/* Do perspective transformation */
	float xscale1 = hfov / tz1, yscale1 = vfov / tz1;
	int x1 = WIDTH / 2 - (int)(tx1 * xscale1);
	float xscale2 = hfov / tz2, yscale2 = vfov / tz2;
	int x2 = WIDTH / 2 - (int)(tx2 * xscale2);
	//if(x1 >= x2 || x2 < now.sx1 || x1 > now.sx2) return; // Only render if it's visible
	/* Acquire the floor and ceiling heights, relative to where the player's view is */
	float yceil  = 50 - plr->position.z;
	float yfloor = 0 - plr->position.z;
	/* Check the edge type. neighbor=-1 means wall, other=boundary between two sectors. */
	//int neighbor = -1;
	//float nyceil=0, nyfloor=0;
	/*
	if(neighbor >= 0) // Is another sector showing through this portal?
	{
		nyceil  = sectors[neighbor].ceil  - player.where.z;
		nyfloor = sectors[neighbor].floor - player.where.z;
	}
	*/
	int y1a  = HEIGHT / 2 - (int)(Yaw(yceil, tz1) * yscale1),  y1b = HEIGHT / 2 - (int)(Yaw(yfloor, tz1) * yscale1);
	int y2a  = HEIGHT / 2 - (int)(Yaw(yceil, tz2) * yscale2),  y2b = HEIGHT / 2 - (int)(Yaw(yfloor, tz2) * yscale2);
	/* The same for the neighboring sector */
	//int ny1a = HEIGHT / 2 - (int)(Yaw(nyceil, tz1) * yscale1), ny1b = HEIGHT / 2 - (int)(Yaw(nyfloor, tz1) * yscale1);
	//int ny2a = HEIGHT / 2 - (int)(Yaw(nyceil, tz2) * yscale2), ny2b = HEIGHT / 2 - (int)(Yaw(nyfloor, tz2) * yscale2);
	int beginx = max(x1, 0), endx = min(x2, WIDTH - 1);
	for(int x = beginx; x <= endx; ++x)
	{
		/* Calculate the Z coordinate for this point. (Only used for lighting.) */
		//int z = ((x - x1) * (tz2 - tz1) / (x2-x1) + tz1) * 8;
		/* Acquire the Y coordinates for our ceiling & floor for this X coordinate. Clamp them. */
		int ya = (x - x1) * (y2a - y1a) / (x2-x1) + y1a, cya = clamp(ya, ytop[x],ybottom[x]); // top
		int yb = (x - x1) * (y2b - y1b) / (x2-x1) + y1b, cyb = clamp(yb, ytop[x],ybottom[x]); // bottom

		/* Render ceiling: everything above this sector's ceiling height. */
		engine_draw_line(eng, (t_point_2d){x, ytop[x]}, (t_point_2d){x, cya-1}, 0xFF0000);
		/* Render floor: everything below this sector's floor height. */
		engine_draw_line(eng, (t_point_2d){x, cyb+1}, (t_point_2d){x, ybottom[x]}, 0xFFFFFF);
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
			sdl_put_pixel(eng->ren, (a.x), (a.y), color);
		i++;
	}
}

void	engine_render_frame(t_engine *eng)
{
	SDL_RenderPresent(eng->ren);
}

void	sdl_clear_window(SDL_Renderer *ren)
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_RenderClear(ren);
}

void	sdl_put_pixel(SDL_Renderer *ren, int x, int y, int color)
{
	SDL_SetRenderDrawColor(ren, (Uint8)(color >> 16), (Uint8)(color >> 8), (Uint8)(color), 255);
	SDL_RenderDrawPoint(ren, x, y);
}
