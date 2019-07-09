/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 17:42:08 by zytrams           #+#    #+#             */
/*   Updated: 2019/07/09 19:56:27 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_draw_line(t_engine *eng, t_point_2d a, t_point_2d b, int color)
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
		if (a.x < WIDTH && a.y < HEIGHT)
			sdl_put_pixel(eng->ren, a.x, a.y, color);
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
