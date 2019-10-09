/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 19:00:51 by zytrams           #+#    #+#             */
/*   Updated: 2019/10/08 22:21:24 by fsmith           ###   ########.fr       */
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
	res->position = (t_point_3d){0, -200.0f, 0.f, 200.0f};
	res->type->anmtn[0]->surface[0] = SDL_CreateRGBSurface(0, w, h, 32, (Uint32)0xff000000,
							(Uint32)0x00ff0000, (Uint32)0x0000ff00, (Uint32)0x000000ff);
	pix = (int *)res->type->anmtn[0]->surface[0]->pixels;
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
	t_point_2d	t1;
	t_point_2d	t2;
	t_point_2d	c1;
	t_point_2d	c2;

	t1.x = spr_obj->position.x - plr.position.x;
	t1.y = spr_obj->position.y - plr.position.y;
	c1.x = t1.x * plr.sinangle - t1.y * plr.cosangle;
	c1.y = t1.x * plr.cosangle + t1.y * plr.sinangle;
	float xscale1 = (WIDTH * hfov) / c1.y, yscale1 = (HEIGHT * vfov) / c1.y;
	int x1 = WIDTH / 2 + (-c1.x * xscale1);
	float yceil = eng->world->sectors_array[sect.sectorno].floor + spr_obj->type->anmtn[0]->surface[0]->h / 4 - plr.position.z;
	float yfloor = eng->world->sectors_array[sect.sectorno].floor - plr.position.z;
	int y1a  = HEIGHT / 2 - (int)((yceil + c1.y * plr.yaw) * yscale1),  y1b = HEIGHT / 2 - (int)((yfloor + c1.y * plr.yaw)  * yscale1);
	int beginx = max(x1, 0);
	engine_render_rescale(spr_obj->type->anmtn[0]->surface[0], surf, 0, zbuff, (t_fix_point_2d){beginx, y1a}, spr_obj->type->anmtn[0]->surface[0]->w * yscale1, spr_obj->type->anmtn[0]->surface[0]->h * yscale1);
}

void		engine_render_rescale(SDL_Surface *surf, SDL_Surface *dest, int z, int *zbuff, t_fix_point_2d point, int new_width, int new_height)
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
	scaleWidth = (double)new_width / (double)surf->w;
	scaleHeight = (double)new_height / (double)surf->h;
	while (cy < new_height)
	{
		cx = 0;
		while (cx < new_width)
		{
			if (zbuff[(cy + point.y) * (WIDTH) + (cx + point.x)] < z && cx >= 0 && cx <= WIDTH)
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
				zbuff[((cy + point.y) * (WIDTH) + (cx + point.x))] = z;
			}
			cx++;
		}
		cy++;
	}
}
