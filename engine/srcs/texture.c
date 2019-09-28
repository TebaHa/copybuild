/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 21:13:21 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/28 12:35:34 by fsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_vline_textured(t_engine *eng, SDL_Surface *surf, t_scaler ty, t_fix_point_3d a, t_fix_point_3d b, int txtx, t_image *texture)
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

int		scaler_next(t_scaler *i)
{
	for(i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca) i->result += i->bop;
	return i->result;
}
