/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:00:51 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/02 20:16:34 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

t_sprobject	*create_test_sprobj(t_engine *eng)
{
	t_sprobject	*res;
	int8_t		red;
	int8_t		green;
	int8_t		blue;
	int8_t		alpha;
	int			color;
	int			x;
	int			y;
	int			w;
	int			h;
	int			*pix;

	res = (t_sprobject *)ft_memalloc(sizeof(t_sprobject));
	w = eng->sprites_buffer[19]->texture.width;
	h = eng->sprites_buffer[19]->texture.height;
	res->angle = 0;
	x = 0;
	res->type = (t_enemy *)ft_memalloc(sizeof(t_enemy));
	res->type->anmtn[0] = (t_sprite *)ft_memalloc(sizeof(t_sprite));
	res->position = (t_point_3d){0, 100, 100, 0};
	res->type->anmtn[0]->surface = SDL_CreateRGBSurface(0, w, h, 32, (Uint32)0xff000000,
							(Uint32)0x00ff0000, (Uint32)0x0000ff00, (Uint32)0x000000ff);
	pix = (int *)res->type->anmtn[0]->surface->pixels;
	while (x < w)
	{
		y = 0;
		while (y < h)
		{
			unsigned offsetd1 = (y * w + x) * 4;
			unsigned offsetd2 = y * w + x ;
			red = (eng->sprites_buffer[19]->texture.data)[offsetd1];
			green = (eng->sprites_buffer[19]->texture.data)[offsetd1 + 2];
			blue = (eng->sprites_buffer[19]->texture.data)[offsetd1 + 2];
			alpha = (eng->sprites_buffer[19]->texture.data)[offsetd1 + 3];
			color = get_rgb((int)red, (int)green, (int)blue, (int)alpha);
			pix[offsetd2] = color;
			y++;
		}
		x++;
	}
	return (res);
}

void		animator_render_sprite_object(t_engine *eng, SDL_Surface *surf, t_player plr, t_sprobject *spr_obj, t_item sect, int *zbuff)
{
	t_wallobj	w_partcle;
	t_point_2d	d1;
	t_point_2d	t1;
	t_point_2d	t2;
	t_point_2d	c1;
	t_point_2d	c2;

	w_partcle.a.x = spr_obj->position.x;
	w_partcle.a.y = spr_obj->position.y;
	w_partcle.b.x = spr_obj->position.x + spr_obj->type->anmtn[0]->surface->w;
	w_partcle.b.y = spr_obj->position.y + spr_obj->type->anmtn[0]->surface->h;
	t1.x = w_partcle.a.x - plr.position.x;
	t1.y = w_partcle.a.y - plr.position.y;
	t2.x = w_partcle.b.x - plr.position.x;
	t2.y = w_partcle.b.y - plr.position.y;
	c1.x = t1.x * plr.sinangle - t1.y * plr.cosangle;
	c1.y = t1.x * plr.cosangle + t1.y * plr.sinangle;
	c2.x = t2.x * plr.sinangle - t2.y * plr.cosangle;
	c2.y = t2.x * plr.cosangle + t2.y * plr.sinangle;
	if (c1.y <= 0 && c2.y <= 0)
		return ;
	float xscale1 = (WIDTH * hfov) / c1.y, yscale1 = (HEIGHT * vfov) / c1.y;
	int x1 = WIDTH / 2 + (-c1.x * xscale1);
	float xscale2 = (WIDTH * hfov) / c2.y, yscale2 = (HEIGHT * vfov) / c2.y;
	int x2 = WIDTH / 2 + (-c2.x * xscale2);
	if(x1 >= x2 || x2 < sect.sx1 || x1 > sect.sx2)
		return ;
	engine_render_rescale(spr_obj->type->anmtn[0]->surface, surf, spr_obj->position.z, zbuff, (t_fix_point_2d){100, 100}, spr_obj->type->anmtn[0]->surface->w / 2, spr_obj->type->anmtn[0]->surface->h / 2);
}

void		engine_render_rescale(SDL_Surface *surf, SDL_Surface *dest, int z, int *zbuff, t_fix_point_2d point, int newWidth, int newHeight)
{
	double			scaleWidth;
	double			scaleHeight;
	int				pixel;
	int				nearestMatch;
	unsigned char	*pixs;
	unsigned char	*pixd;
	int				cy;
	int				cx;

	cy = 0;
	pixs = (unsigned char *)surf->pixels;
	pixd = (unsigned char *)dest->pixels;
	if(surf == NULL)
		return ;
	scaleWidth = (double)newWidth / (double)surf->w;
	scaleHeight = (double)newHeight / (double)surf->h;
	while (cy < newHeight)
	{
		cx = 0;
		while (cx < newWidth)
		{
			pixel = ((cy + point.y) * (WIDTH) + (cx + point.x)) * 4;
			nearestMatch =  (((int)(cy / scaleHeight) * (surf->w)) + ((int)(cx / scaleWidth))) * 4;
			if (pixs[nearestMatch + 3] != 0)
			{
				pixd[pixel] = pixs[nearestMatch];
				pixd[pixel + 1] = pixs[nearestMatch + 1];
				pixd[pixel + 2] = pixs[nearestMatch + 2];
				pixd[pixel + 3] = pixs[nearestMatch + 3];
			}
			cx++;
		}
		cy++;
	}
}