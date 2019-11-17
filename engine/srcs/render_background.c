/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:21:26 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/16 19:02:26 by zytrams          ###   ########.fr       */
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
		SDL_Surface *surf, float yaw, float plrangle)
{
	int	x;
	int	y;
	int	sx;
	int	sy;
	int	oy;
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
	oy = ((((HEIGHT) / (400)) * ((yaw + 3.0) * 100)));
	while (x < WIDTH)
	{
		if (sx >= WIDTH)
			sx = 0;
		y = 0;
		sy = oy;
		while (y < HEIGHT - 1 && sy < eng->sky->h - 1)
		{
			red = ((unsigned char *)spix)
			[((sy * eng->sky->w + sx) * 4)];
			green = ((unsigned char *)spix)
			[((sy * eng->sky->w + sx) * 4) + 1];
			blue = ((unsigned char *)spix)
			[((sy * eng->sky->w + sx) * 4) + 2];
			dpix[y * surf->w + x] =
			get_rgb(red, green, blue, 255);
			y++;
			sy++;
		}
		sx++;
		x++;
	}
	SDL_UnlockSurface(surf);
	SDL_UnlockSurface(eng->sky);
}
