/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:21:26 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/02 03:23:48 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <engine.h>

void	engine_find_background(t_engine *eng)
{
	int			i;

	i = 0;
	while (i < eng->stats.textures_count)
	{
		if (ft_strcmp(eng->texture_buffer[i][0].filename, "sky.png") == 0)
		{
			eng->sky = util_transform_texture_to_sprite
			(&eng->texture_buffer[i]->texture);
			break ;
		}
		i++;
	}
}


void	engine_draw_background(t_engine *eng,
		SDL_Surface *surf, int plrangle)
{
	int	x;
	int	y;
	int	sx;
	int	*spix;
	int	*dpix;
	int	red;
	int green;
	int blue;
	int	xscale;

	xscale = 4;
	SDL_LockSurface(surf);
	SDL_LockSurface(eng->sky);
	x = 0;
	spix = (int *)eng->sky->pixels;
	dpix = (int *)surf->pixels;
	sx = (WIDTH / 360) * (plrangle);
	while (x <= WIDTH)
	{
		if (sx > WIDTH)
			sx = 0;
		y = 0;
		while (y <= HEIGHT)
		{
			red = ((unsigned char *)spix)
			[((y / 2 * eng->sky->w + sx / xscale) * 4)];
			green = ((unsigned char *)spix)
			[((y / 2 * eng->sky->w + sx / xscale) * 4) + 1];
			blue = ((unsigned char *)spix)
			[((y / 2 * eng->sky->w + sx / xscale) * 4) + 2];
			dpix[y * surf->w + x] =
			get_rgb(red, green, blue, 255);
			y++;
		}
		sx++;
		x++;
	}
	SDL_UnlockSurface(surf);
	SDL_UnlockSurface(eng->sky);
}