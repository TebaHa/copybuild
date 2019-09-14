/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zytrams <zytrams@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 10:59:30 by zytrams           #+#    #+#             */
/*   Updated: 2019/09/14 13:09:33 by zytrams          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <engine.h>

void		engine_draw_hud(t_engine *eng, SDL_Surface *surf)
{
	int		i;
	int		x;
	int		y;
	int		tx;
	int		ty;
	int		*pix;
	int		red;
	int		green;
	int		blue;
	int		alpha;
	t_image	*img;

	i = 0;
	pix = (int *)surf->pixels;
	while (i < eng->stats.sprites_count)
	{
		if (ft_strcmp(eng->sprites_buffer[i]->filename, "hud.png") == 0)
		{
			img = &eng->sprites_buffer[i]->texture;
			break;
		}
		i++;
	}
	x = 0;
	tx = (WIDTH - img->width) / 2;
	while (x < img->width)
	{
		y = 0;
		ty = HEIGHT - img->height;
		while (y < img->height)
		{
			if (img->data[(y * img->channels * img->width + x * img->channels) + 3] == 255)
			{
				red = img->data[(y * img->channels * img->width + x * img->channels)];
				green = img->data[(y * img->channels * img->width + x * img->channels) + 1];
				blue = img->data[(y * img->channels * img->width + x * img->channels) + 2];
				pix[ty * WIDTH + tx] = get_rgb(red, green, blue, 255);
			}
			y++;
			ty++;
		}
		tx++;
		x++;
	}
}
