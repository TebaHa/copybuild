/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 21:13:21 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/03 05:01:02 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_vline_textured(t_engine *eng, SDL_Surface *surf, t_scaler ty, t_fix_point_3d a, t_fix_point_3d b, int txtx, int z, int *zbuff, t_image *texture)
{
	int		y1;
	int		y2;
	int8_t	red;
	int8_t	green;
	int8_t	blue;
	int		color;
	int *pix = (int *)surf->pixels;

	y1 = clamp(a.y, 0, HEIGHT - 1);
	y2 = clamp(b.y, 0, HEIGHT - 1);
	pix += y1 * WIDTH + a.x;
	for(int y = y1; y <= y2; ++y)
	{
		unsigned txty = scaler_next(&ty);
		unsigned offset = (((txty % texture->height) * texture->width) + (txtx % texture->width)) * texture->channels;
		if ((texture->data)[offset + 3] == 255)
		{
			red = (texture->data)[offset];
			green = (texture->data)[offset + 1];
			blue = (texture->data)[offset + 2];
			color = get_rgb((int)red, (int)green, (int)blue, 255);
			*pix = color;
			pix += WIDTH;
		}
	}
}

void	engine_vline_textured_sprite(t_engine *eng, SDL_Surface *surf, t_scaler ty, t_fix_point_3d a, t_fix_point_3d b, int txtx, int z, int *zbuff, t_sprite *texture)
{
	int				y1;
	int				y2;
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
	int				color;
	uint8_t			*pixs;
	int				*pixd;

	pixs = (unsigned char *)texture->surface->pixels;
	pixd = (int *)surf->pixels;
	y1 = clamp(a.y, 0, HEIGHT - 1);
	y2 = clamp(b.y, 0, HEIGHT - 1);
	pixd += y1 * WIDTH + a.x;
	for(int y = y1; y <= y2; ++y)
	{
		unsigned txty = scaler_next(&ty);
		unsigned offset = (((txty % texture->surface->h) * texture->surface->w) + (txtx % texture->surface->w)) * 4;
		if ((pixs)[offset + 3] == 255)
		{
			red = (pixs)[offset];
			green = (pixs)[offset + 1];
			blue = (pixs)[offset + 2];
			color = get_rgb((int)red, (int)green, (int)blue, 255);
			*pixd = color;
		}
		pixd += WIDTH;
	}
}

void	engine_vline_textured_surface(t_engine *eng, SDL_Surface *surf, t_scaler ty, t_fix_point_3d a, t_fix_point_3d b, int txtx, int z, int *zbuff, SDL_Surface *texture)
{
	int				y1;
	int				y2;
	uint8_t			red;
	uint8_t			green;
	uint8_t			blue;
	int				color;
	uint8_t			*pixs;
	int				*pixd;

	pixs = (unsigned char *)texture->pixels;
	pixd = (int *)surf->pixels;
	y1 = clamp(a.y, 0, HEIGHT - 1);
	y2 = clamp(b.y, 0, HEIGHT - 1);
	pixd += y1 * WIDTH + a.x;
	for(int y = y1; y <= y2; ++y)
	{
		unsigned txty = scaler_next(&ty);
		unsigned offset = (((txty % texture->h) * texture->w) + (txtx % texture->w)) * 4;
		if ((pixs)[offset + 3] == 255)
		{
			red = (pixs)[offset];
			green = (pixs)[offset + 1];
			blue = (pixs)[offset + 2];
			color = get_rgb((int)red, (int)green, (int)blue, 255);
			*pixd = color;
		}
		pixd += WIDTH;
	}
}

int		scaler_next(t_scaler *i)
{
	for(i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca) i->result += i->bop;
	return i->result;
}
