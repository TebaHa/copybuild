/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:21:26 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/02 07:43:47 by zytrams          ###   ########.fr       */
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
		SDL_Surface *surf, float plrangle)
{
	int	x;
	int	y;
	int	sx;
	int	*spix;
	int	*dpix;
	int	red;
	int green;
	int blue;

	SDL_LockSurface(surf);
	SDL_LockSurface(eng->sky);
	x = 0;
	spix = (int *)eng->sky->pixels;
	dpix = (int *)surf->pixels;
	sx = ((float)((float)eng->sky->w / 360)) * ((int)(plrangle * 180 / M_PI) % 360);
	while (x <= WIDTH)
	{
		if (sx > WIDTH - 3)
			sx = 0;
		y = 0;
		while (y <= HEIGHT)
		{
			red = ((unsigned char *)spix)
			[((y * eng->sky->w + sx) * 4)];
			green = ((unsigned char *)spix)
			[((y * eng->sky->w + sx) * 4) + 1];
			blue = ((unsigned char *)spix)
			[((y * eng->sky->w + sx) * 4) + 2];
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