/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 21:13:21 by zytrams           #+#    #+#             */
/*   Updated: 2019/08/26 20:36:35 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_vline_textured(t_engine *eng, t_scaler ty, t_fix_point_3d a, t_fix_point_3d b, int txtx, t_image *texture)
{
	int		y1;
	int		y2;
	int8_t	red;
	int8_t	green;
	int8_t	blue;
	int		color;
	int *pix = (int*) eng->surface->pixels;

	y1 = clamp(a.y, 0, HEIGHT - 1);
	y2 = clamp(b.y, 0, HEIGHT - 1);
	pix += y1 * WIDTH + a.x;
	for(int y = y1; y <= y2; ++y)
	{
		unsigned txty = scaler_next(&ty);
		red = (texture->data)[(((txty % texture->height) * texture->width) + (txtx % texture->width)) * texture->channels];
		green = (texture->data)[(((txty % texture->height) * texture->width) + (txtx % texture->width)) * texture->channels + 1];
		blue = (texture->data)[(((txty % texture->height) * texture->width) + (txtx % texture->width)) * texture->channels + 2];
		color = get_rgb((int)red, (int)green, (int)blue, 255);
		*pix = color;
		pix += WIDTH;
	}
}

int		scaler_next(t_scaler *i)
{
	for(i->cache += i->fd; i->cache >= i->ca; i->cache -= i->ca) i->result += i->bop;
	return i->result;
}
