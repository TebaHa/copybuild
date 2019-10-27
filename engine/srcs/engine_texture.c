/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 21:13:21 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/18 20:37:27 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_vline_textured(SDL_Surface *surf, t_scaler ty,
		t_vline1_in din, t_image *texture)
{
	t_vline1	d;

	d.pixd = (int *)surf->pixels;
	d.y1 = clamp(din.a.y, 0, HEIGHT - 1);
	d.y2 = clamp(din.b.y, 0, HEIGHT - 1);
	d.pixd += d.y1 * WIDTH + din.a.x;
	d.y = d.y1;
	while (d.y <= d.y2)
	{
		d.txty = scaler_next(&ty);
		d.offset = (((d.txty % texture->height) * texture->width)
		+ (din.txtx % texture->width)) * texture->channels;
		if ((texture->data)[d.offset + 3] == 255)
		{
			d.red = (texture->data)[d.offset];
			d.green = (texture->data)[d.offset + 1];
			d.blue = (texture->data)[d.offset + 2];
			d.color = get_rgb((int)d.red, (int)d.green, (int)d.blue, 255);
			*d.pixd = d.color;
		}
		d.pixd += WIDTH;
		d.y++;
	}
}

void	engine_vline_textured_sprite(SDL_Surface *surf, t_scaler ty,
		t_vline1_in din, t_sprite *texture)
{
	t_vline1	d;

	d.pixs = (unsigned char *)texture->surface[0]->pixels;
	d.pixd = (int *)surf->pixels;
	d.y1 = clamp(din.a.y, 0, HEIGHT - 1);
	d.y2 = clamp(din.b.y, 0, HEIGHT - 1);
	d.pixd += d.y1 * WIDTH + din.a.x;
	d.y = d.y1;
	while (d.y <= d.y2)
	{
		d.txty = scaler_next(&ty);
		d.offset = (((d.txty % texture->surface[0]->h)
		* texture->surface[0]->w) + (din.txtx % texture->surface[0]->w)) * 4;
		if ((d.pixs)[d.offset + 3] == 255)
		{
			d.red = (d.pixs)[d.offset];
			d.green = (d.pixs)[d.offset + 1];
			d.blue = (d.pixs)[d.offset + 2];
			d.color = get_rgb((int)d.red, (int)d.green, (int)d.blue, 255);
			*d.pixd = d.color;
		}
		d.pixd += WIDTH;
		d.y++;
	}
}

void	engine_vline_textured_surface(SDL_Surface *surf, t_scaler ty,
		t_vline1_in din, SDL_Surface *texture)
{
	t_vline1	d;

	d.pixs = (unsigned char *)texture->pixels;
	d.pixd = (int *)surf->pixels;
	d.y1 = clamp(din.a.y, 0, HEIGHT - 1);
	d.y2 = clamp(din.b.y, 0, HEIGHT - 1);
	d.pixd += d.y1 * WIDTH + din.a.x;
	d.y = d.y1;
	while (d.y <= d.y2)
	{
		d.txty = scaler_next(&ty);
		d.offset = (((d.txty % texture->h) * texture->w)
		+ (din.txtx % texture->w)) * 4;
		if ((d.pixs)[d.offset + 3] == 255)
		{
			d.red = (d.pixs)[d.offset];
			d.green = (d.pixs)[d.offset + 1];
			d.blue = (d.pixs)[d.offset + 2];
			d.color = get_rgb((int)d.red, (int)d.green, (int)d.blue, 255);
			*d.pixd = d.color;
		}
		d.pixd += WIDTH;
		d.y++;
	}
}

int		scaler_next(t_scaler *i)
{
	i->cache += i->fd;
	while (i->cache >= i->ca)
	{
		i->result += i->bop;
		i->cache -= i->ca;
	}
	return (i->result);
}
