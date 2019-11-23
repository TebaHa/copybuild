/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 17:21:26 by zytrams           #+#    #+#             */
/*   Updated: 2019/11/23 15:50:22 by zytrams          ###   ########.fr       */
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
			eng->sky = util_transform_texture_to_sprite(&eng->
			texture_buffer[i]->texture);
			break ;
		}
		i++;
	}
}

void	engine_draw_background(t_engine *eng,
		SDL_Surface *surf, float yaw, float plrangle)
{
	t_bg	bg;

	SDL_LockSurface(surf);
	SDL_LockSurface(eng->sky);
	bg.x = 0;
	bg.spix = (int *)eng->sky->pixels;
	bg.dpix = (int *)surf->pixels;
	bg.sx = ((float)((float)eng->sky->w / 360))
	* ((int)(plrangle * 180 / M_PI) % 360);
	bg.oy = ((((HEIGHT) / (400)) * ((yaw + 3.0) * 100)));
	engine_draw_background_help(eng, surf, &bg);
	SDL_UnlockSurface(surf);
	SDL_UnlockSurface(eng->sky);
}

void	engine_draw_background_help(t_engine *eng,
		SDL_Surface *surf, t_bg *bg)
{
	while (bg->x < WIDTH)
	{
		if (bg->sx >= WIDTH)
			bg->sx = 0;
		bg->y = 0;
		bg->sy = bg->oy;
		while (bg->y < HEIGHT - 1 && bg->sy < eng->sky->h - 1)
		{
			bg->red = ((unsigned char *)bg->spix)
			[((bg->sy * eng->sky->w + bg->sx) * 4)];
			bg->green = ((unsigned char *)bg->spix)
			[((bg->sy * eng->sky->w + bg->sx) * 4) + 1];
			bg->blue = ((unsigned char *)bg->spix)
			[((bg->sy * eng->sky->w + bg->sx) * 4) + 2];
			bg->dpix[bg->y * surf->w + bg->x] =
			get_rgb(bg->red, bg->green, bg->blue, 255);
			bg->y++;
			bg->sy++;
		}
		bg->sx++;
		bg->x++;
	}
}
