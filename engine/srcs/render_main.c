/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 20:21:16 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/19 20:24:35 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

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
	p = (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
	*(int *)p = color;
}
